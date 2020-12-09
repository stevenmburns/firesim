#!/bin/bash

make TARGET_PROJECT=midasexamples SCALA_TEST=firesim.midasexamples.SchExcJsonF1Test VCS_FLAGS="-file /nfs/sc/disks/scl.work.52/ppt/users/smburns/luna/bld/schexc/vcs_dut.f -f /nfs/sc/disks/scl.work.52/ppt/users/smburns/luna/bld/schexc/vlog_dut.files -top emul -e vcs_main" testOnly
