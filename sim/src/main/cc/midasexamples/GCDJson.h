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

class GCDJson_t: virtual simif_t
{
public:

  json j;
  std::optional<unsigned int> state_reset;
  std::map<std::string,std::optional<std::string> > state_values;
  std::map<std::string,size_t> input_vars;
  std::map<std::string,size_t> output_vars;

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

    std::map<std::string,std::string> output_values;

    const auto & j2 = it->at("changes");
    for (json::const_iterator it2 = j2.begin(); it2 != j2.end(); ++it2) {
      std::string var(it2->at("variable"));
      std::string val(it2->at("value"));

      std::cout << "\t" << var << " " << val << std::endl;
      {
        auto it3 = output_vars.find(var);
        if ( it3 != output_vars.end()) {
          output_values.insert(std::make_pair( it3->first, val));
        }
      }
      {
        auto it3 = state_values.find(var);
        if ( it3 != state_values.end()) {
          it3->second = std::optional<std::string>(val);
        }
      }
      if ( var == "clock") {
        optClock = std::optional<unsigned int>(std::stoi(val,0,2));
      }

    }

    assert(optClock);

    assert( time % 1000 == 0);
    if ( *optClock == 1) {
      assert( time % 2000 == 0);
      step(1);
    } else {
      assert( time % 2000 == 1000);
    }

    if ( state_reset && *state_reset == 0) {
      for (auto it3 = input_vars.begin(); it3 != input_vars.end(); ++it3) {
        expectWithStr( it3->second, *state_values[it3->first]);
      }
    }

    for (auto it3 = output_values.begin(); it3 != output_values.end(); ++it3) {
      pokeWithStr( output_vars[it3->first], it3->second);
    }

    {
      // Do the assignment to state_reset after the test on state_reset above
      auto it3 = output_values.find("reset");
      if ( it3 != output_values.end()) {
        state_reset = std::optional<unsigned int>(std::stoi(it3->second,0,2));
      }
    }

  }


  GCDJson_t(int argc, char** argv) {

    std::string filename = "/nfs/site/disks/scl.work.50/ash/users/smburns/json-vcd/out.json";
    std::ifstream ifs(filename);
    if (ifs.fail()) {
      std::cout << "Cannot open file: " << filename << " for reading." << std::endl;
      assert(false);
    } else {
      j = json::parse(ifs);
      ifs.close();
    }

    output_vars.insert(std::make_pair( "io_a", io_a));
    output_vars.insert(std::make_pair( "io_b", io_b));
    output_vars.insert(std::make_pair( "io_e", io_e));
    output_vars.insert(std::make_pair( "reset", reset));

    input_vars.insert(std::make_pair( "io_v", io_v));
    input_vars.insert(std::make_pair( "io_z", io_z));

    for ( auto it3 = input_vars.begin(); it3 != input_vars.end(); ++it3) {
      state_values.insert( std::make_pair(it3->first, std::optional<std::string>()));
    }
  }


  void run() {
    for ( json::iterator it = j.begin(); it != j.end(); ++it) {
      process_time(it);
    }
  }
};
