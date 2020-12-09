#!/bin/bash

make TARGET_PROJECT=midasexamples SCALA_TEST=firesim.midasexamples.GCDJsonF1Test VCS_FLAGS="-top emul -e vcs_main" testOnly
