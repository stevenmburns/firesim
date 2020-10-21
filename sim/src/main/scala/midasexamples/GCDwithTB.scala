//See LICENSE for license details.

package firesim.midasexamples

import chisel3._
import freechips.rocketchip.config.Parameters
import chisel3.util.unless
import chisel3.experimental.{withClock, annotate}

import midas.widgets.PeekPokeBridge
import midas.targetutils.FAMEModelAnnotation


class GCDTB extends Module {
  val io = IO(Flipped(new GCDIO))

  val state = RegInit( 0.U(8.W))

  io.e := false.B
  io.a := DontCare
  io.b := DontCare

  val a = 360
  val b = 27
  val z = 9

  when (state === 0.U) {
    io.a := a.U
    io.b := b.U 
    io.e := true.B
    state := 1.U
  } .elsewhen ( state === 1.U) {
    io.e := false.B
    when ( io.v) {
      assert( io.z === z.U)
    }
  }
}


class GCDwithTBDUT extends Module {
  val io = IO(new Bundle {
    val done = Output(Bool())
  })

  val tb = Module(new GCDTB())
  val dut = Module(new GCDDUT())

  io.done := dut.io.v

  tb.io <> dut.io
}

class GCDwithTB(implicit p: Parameters) extends PeekPokeMidasExampleHarness(() => new GCDwithTBDUT)
