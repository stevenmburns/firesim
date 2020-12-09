#!/bin/bash

vcs -full64 -quiet -timescale=1ns/1ps +v2k +rad +vcs+initreg+random +vcs+lic+wait -notice -line +lint=all,noVCDE,noONGS,noUI -quiet -debug_pp +no_notifier -cpp g++ -Mdir=/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/SchExcJson-debug.csrc +vc+list -CFLAGS " -DDESIGNDRIVERCLASS=SchExcJson_t -DDESIGNNAME_SchExcJson -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/src/main/cc -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc/ -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/src/main/cc/midasexamples -g -Wno-unused-variable -O2 -I/nfs/site/disks/sc_atsgt_77621/nillikai/vcs_patches_lc/vcs_1906_05272020//include -D RTLSIM -std=c++17 -Wall -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/target-design/chipyard/tools/DRAMSim2 -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/target-design/chipyard/generators/testchipip/src/main/resources/testchipip/csrc -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc -I/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/utils -include /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/SchExcJson-const.h -D_GNU_SOURCE -DVCS -I/nfs/site/disks/sc_atsgt_77621/nillikai/vcs_patches_lc/vcs_1906_05272020//include" -LDFLAGS "  -lrt -L/nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config -lstdc++ -lpthread -lgmp -lmidas " -sverilog -assert svaext +define+CLOCK_PERIOD=1.0 +define+RANDOMIZE_GARBAGE_ASSIGN +define+RANDOMIZE_INVALID_ASSIGN -file /nfs/sc/disks/scl.work.52/ppt/users/smburns/luna/bld/schexc/vcs_dut.f -f /nfs/sc/disks/scl.work.52/ppt/users/smburns/luna/bld/schexc/vlog_dut.files -top FPGATop -e vcs_main +define+DEBUG \
-o /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/SchExcJson-debug /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/SchExcJson-const.vh /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/FPGATop.v /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/verilog/BUFGCE.v /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/verilog/vcs_top.v /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/src/main/cc/midasexamples/Driver.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/uart.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/groundtest.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/dromajo.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/blockdev.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/serial.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/simplenic.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/firesim-lib/src/main/cc//bridges/tracerv.cc  /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/bridges/synthesized_assertions.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/bridges/fased_memory_timing_model.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/bridges/autocounter.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/bridges/synthesized_prints.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/bridges/address_map.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/simif.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/simif_emul.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/midas/src/main/cc/emul/mmio.cc /nfs/sc/disks/scl.work.52/ppt/users/smburns/Berkeley/firesim/sim/generated-src/f1/SchExcJson-NoConfig-HostDebugFeatures_DefaultF1Config/libmidas.a emul/vcs-harness.cc
