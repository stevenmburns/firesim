//See LICENSE for license details.

#include "simif.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

#include <set>
#include <map>
#include <optional>

#include "gmp.h"

//#include "svdpi.h"

using namespace nlohmann;

void replaceStrChar( std::string& str, const std::string& replace, char ch) {
  size_t found = str.find_first_of(replace);
  while (found != std::string::npos) {
    str[found] = ch;
    found = str.find_first_of(replace, found+1);
  }
}

class GCD2Json_t: virtual simif_t
{
public:

  json j;
  std::optional<unsigned int> state_reset;
  std::map<std::string,std::optional<std::string> > state_values;
  std::map<std::string,size_t> output_vars;
  std::map<std::string,size_t> input_vars;

  int clock_edge_count;

  void process_time( const json::iterator& it) {
    int time = it->at("time");
    std::cout << "Time: " << time << std::endl;

    auto str2mpz = []( mpz_t n, const std::string& str) {
      mpz_init(n);
      mpz_set_ui(n, 0);
      mpz_set_str(n, str.c_str(), 2);
    };

    auto pokeWithStr = [&]( size_t id, const std::string& str){
       mpz_t value;
       str2mpz( value, str);
       poke( id, value);
       mpz_clear(value);
    };

    auto expectWithStr = [&]( size_t id, const std::string& str){
       mpz_t value;
       str2mpz( value, str);
       expect( id, value);
       mpz_clear(value);
    };

    std::optional<unsigned int> optClock;

    std::map<std::string,std::string> input_values;

    const auto & j2 = it->at("changes");
    for (json::const_iterator it2 = j2.begin(); it2 != j2.end(); ++it2) {
      std::string var(it2->at("variable"));
      std::string val(it2->at("value"));

      std::string val0(val);
      replaceStrChar( val0, "xz", '0');

      std::cout << "\t" << var << " " << val << " (" << val0 << ")" << std::endl;
      if ( var == "clock") {
        optClock = std::optional<unsigned int>(std::stoi(val,0,2));
      } else {
	{
	  auto it3 = input_vars.find(var);
	  if ( it3 != input_vars.end()) {
	    input_values.insert(std::make_pair( it3->first, val0));
	  }
	}
	{
	  auto it3 = state_values.find(var);
	  if ( it3 != state_values.end()) {
	    if ( val == val0) {
	      it3->second = std::optional<std::string>(val);
	    } else {
	      it3->second = std::nullopt;
	    }
	  }
	}
      }
    }

    if ( optClock.has_value() && *optClock == 1) {
      std::cout << "Clock Edge " << clock_edge_count << " at time " << time << std::endl;
      step(1);
      clock_edge_count += 1;

    }

    for (auto it3 = input_values.begin(); it3 != input_values.end(); ++it3) {
      pokeWithStr( input_vars[it3->first], it3->second);
    }

    if ( state_reset && *state_reset == 0) {
      for (auto it3 = output_vars.begin(); it3 != output_vars.end(); ++it3) {
	auto st_opt = state_values[it3->first];
	if ( st_opt.has_value()) {
	  expectWithStr( it3->second, *st_opt);
	}
      }
    }

    {
      // Do the assignment to state_reset after the test on state_reset above
      auto it3 = input_values.find("reset");
      if ( it3 != input_values.end()) {
        state_reset = std::optional<unsigned int>(std::stoi(it3->second,0,2));
      }
    }

  }


  GCD2Json_t(int argc, char** argv) {

    std::string filename = "/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/out.json";
    std::ifstream ifs(filename);
    if (ifs.fail()) {
      std::cout << "Cannot open file: " << filename << " for reading." << std::endl;
      assert(false);
    } else {
      j = json::parse(ifs);
      ifs.close();
    }

    input_vars.insert(std::make_pair( "io_a", io_a));
    input_vars.insert(std::make_pair( "io_b", io_b));
    input_vars.insert(std::make_pair( "io_e", io_e));
    input_vars.insert(std::make_pair( "reset", reset));

    output_vars.insert(std::make_pair( "io_v", io_v));
    output_vars.insert(std::make_pair( "io_z", io_z));

    for ( auto it3 = output_vars.begin(); it3 != output_vars.end(); ++it3) {
      state_values.insert( std::make_pair(it3->first, std::optional<std::string>()));
    }
  }


  void run() {
    clock_edge_count = 0;
    for ( json::iterator it = j.begin(); it != j.end(); ++it) {
      process_time(it);
    }
  }
};
