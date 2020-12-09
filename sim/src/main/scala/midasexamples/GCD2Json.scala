//See LICENSE for license details.

package firesim.midasexamples

import chisel3._
import chisel3.util._

import freechips.rocketchip.config.Parameters
import chisel3.util.unless
import chisel3.experimental.{withClock, annotate}

import midas.widgets.PeekPokeBridge
import midas.targetutils.FAMEModelAnnotation

class GCDIO2_no_master_clk extends Bundle {
  val a  = Input(UInt(16.W))
  val b  = Input(UInt(16.W))
  val e  = Input(Bool())
  val z  = Output(UInt(16.W))
  val v  = Output(Bool())
}

class GCDIO2 extends Bundle {
  val master_clk = Input(Clock())    
  val a  = Input(UInt(16.W))
  val b  = Input(UInt(16.W))
  val e  = Input(Bool())
  val z  = Output(UInt(16.W))
  val v  = Output(Bool())
}

class GCDInVerilog extends BlackBox with HasBlackBoxResource {
  val io = IO(new GCDIO2)      
  //addResource("/verilog/schexc.v")        
}

class GCD2_top extends Module {
  val io = IO(new GCDIO2_no_master_clk)
  val m = Module(new GCDInVerilog)
  m.io.master_clk := clock
  m.io.a := io.a 
  m.io.b := io.b 
  m.io.e := io.e 
  io.z := m.io.z 
  io.v := m.io.v 
}

class GCD2Json(implicit p: Parameters) extends PeekPokeMidasExampleHarness(() => new GCD2_top)
