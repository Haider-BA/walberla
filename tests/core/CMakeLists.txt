###################################################################################################
#
# Tests for core module
#
###################################################################################################

########
# cell #
########

waLBerla_compile_test( FILES cell/CellTest.cpp )
waLBerla_execute_test( NAME CellTest )

waLBerla_compile_test( FILES cell/CellIntervalTest.cpp )
waLBerla_execute_test( NAME CellIntervalTest )

##########
# config #
##########

waLBerla_compile_test( FILES config/ConfigTest.cpp )
waLBerla_execute_test( NAME ConfigTest COMMAND $<TARGET_FILE:ConfigTest> ${CMAKE_CURRENT_SOURCE_DIR}/config/ConfigTest.dat )

waLBerla_compile_test( FILES config/PropertyTreeTest.cpp)
#waLBerla_execute_test(NAME PropertyTreeTest COMMAND $<TARGET_FILE:PropertyTreeTest> )


waLBerla_compile_test( FILES config/MultiArrayIOTest.cpp )
waLBerla_execute_test( NAME MultiArrayIOTest COMMAND $<TARGET_FILE:MultiArrayIOTest> )


#########
# debug #
#########

waLBerla_compile_test( FILES debug/DebugTest.cpp)
waLBerla_execute_test( NAME DebugTest )

waLBerla_compile_test( FILES debug/CheckMacroTest.cpp )
waLBerla_execute_test( NAME CheckMacroTest )

waLBerla_compile_test( FILES debug/PrintStacktraceTest.cpp )

###########
# logging #
###########

waLBerla_compile_test( FILES logging/LoggingTest.cpp)
waLBerla_execute_test( NAME LoggingTest )

########
# math #
########

waLBerla_compile_test( FILES math/PrimesTest.cpp )
waLBerla_execute_test( NAME PrimesTest )

waLBerla_compile_test( FILES math/RandomTest.cpp )
waLBerla_execute_test( NAME RandomTest )

waLBerla_compile_test( FILES math/SampleTest.cpp )
waLBerla_execute_test( NAME SampleTest1Proc  COMMAND $<TARGET_FILE:SampleTest> )
waLBerla_execute_test( NAME SampleTest4Proc  COMMAND $<TARGET_FILE:SampleTest> PROCESSES 4  )
waLBerla_execute_test( NAME SampleTest10Proc COMMAND $<TARGET_FILE:SampleTest> PROCESSES 10 LABELS longrun CONFIGURATIONS Release RelWithDbgInfo )

waLBerla_compile_test( FILES math/DistributedSampleTest.cpp )
waLBerla_execute_test( NAME DistributedSampleTest1Proc  COMMAND $<TARGET_FILE:DistributedSampleTest> )
waLBerla_execute_test( NAME DistributedSampleTest4Proc  COMMAND $<TARGET_FILE:DistributedSampleTest> PROCESSES 4  )
waLBerla_execute_test( NAME DistributedSampleTest10Proc COMMAND $<TARGET_FILE:DistributedSampleTest> PROCESSES 10 LABELS longrun )

waLBerla_compile_test( FILES math/ParserTest.cpp)
waLBerla_execute_test( NAME ParserTest )

waLBerla_compile_test( FILES math/PlaneTest.cpp )
waLBerla_execute_test( NAME PlaneTest )

waLBerla_compile_test( FILES math/MatrixVector2Test.cpp )
waLBerla_execute_test( NAME MatrixVector2Test )


waLBerla_compile_test( FILES math/Matrix3Test.cpp )
waLBerla_execute_test( NAME Matrix3Test )

waLBerla_compile_test( FILES math/GenericAABBTest.cpp DEPENDS stencil domain_decomposition )
waLBerla_execute_test( NAME GenericAABBTest )

waLBerla_compile_test( FILES math/PhysicalCheckTest.cpp DEPENDS stencil )
waLBerla_execute_test( NAME PhysicalCheckTest 
                      COMMAND $<TARGET_FILE:PhysicalCheckTest>  ${CMAKE_CURRENT_SOURCE_DIR}/math/PhysicalCheckTestInput.prm )


waLBerla_compile_test( FILES math/FastInvSqrtTest.cpp )
waLBerla_execute_test( NAME FastInvSqrtTest )

########################
# math/equation_system #
########################

waLBerla_compile_test( FILES math/equation_system/EquationSolverTest.cpp )
waLBerla_execute_test( NAME EquationSolverTest )

#######
# mpi #
#######

waLBerla_compile_test( FILES mpi/BufferTest.cpp )
waLBerla_execute_test( NAME BufferTest )

if( WALBERLA_BUILD_WITH_BOOST_THREAD )
   waLBerla_compile_test( FILES mpi/BufferSystemTest.cpp )
   waLBerla_execute_test( NAME BufferSystemTest PROCESSES 4 )
endif()

waLBerla_compile_test( FILES mpi/BroadcastTest.cpp )
waLBerla_execute_test( NAME BroadcastTest1 COMMAND $<TARGET_FILE:BroadcastTest> )
waLBerla_execute_test( NAME BroadcastTest4 COMMAND $<TARGET_FILE:BroadcastTest> PROCESSES 4)

waLBerla_compile_test( FILES mpi/ReduceTest.cpp )
waLBerla_execute_test( NAME ReduceTest1 COMMAND $<TARGET_FILE:ReduceTest> )
waLBerla_execute_test( NAME ReduceTest4 COMMAND $<TARGET_FILE:ReduceTest> PROCESSES 4)

waLBerla_compile_test( FILES mpi/GatherTest.cpp )
waLBerla_execute_test( NAME GatherTest1 COMMAND $<TARGET_FILE:GatherTest> )
waLBerla_execute_test( NAME GatherTest4 COMMAND $<TARGET_FILE:GatherTest> PROCESSES 4)

waLBerla_compile_test( FILES mpi/GathervTest.cpp )
waLBerla_execute_test( NAME GathervTest1 COMMAND $<TARGET_FILE:GathervTest> )
waLBerla_execute_test( NAME GathervTest4 COMMAND $<TARGET_FILE:GathervTest> PROCESSES 4)

waLBerla_compile_test( FILES mpi/MPITextFileTest.cpp )
waLBerla_execute_test( NAME MPITextFileTest1 COMMAND $<TARGET_FILE:MPITextFileTest> MPI_Testfile_1.txt 16 )
waLBerla_execute_test( NAME MPITextFileTest4 COMMAND $<TARGET_FILE:MPITextFileTest> MPI_Testfile_4.txt 16 PROCESSES 4 )
waLBerla_execute_test( NAME MPITextFileTest8 COMMAND $<TARGET_FILE:MPITextFileTest> MPI_Testfile_8.txt 16 PROCESSES 8 )

waLBerla_compile_test( FILES mpi/SetReductionTest.cpp )
waLBerla_execute_test( NAME SetReductionTest1  COMMAND $<TARGET_FILE:SetReductionTest> )
waLBerla_execute_test( NAME SetReductionTest2  COMMAND $<TARGET_FILE:SetReductionTest> PROCESSES 2 )
waLBerla_execute_test( NAME SetReductionTest3  COMMAND $<TARGET_FILE:SetReductionTest> PROCESSES 3 )
waLBerla_execute_test( NAME SetReductionTest4  COMMAND $<TARGET_FILE:SetReductionTest> PROCESSES 4 )
waLBerla_execute_test( NAME SetReductionTest5  COMMAND $<TARGET_FILE:SetReductionTest> PROCESSES 5 )
waLBerla_execute_test( NAME SetReductionTest27 COMMAND $<TARGET_FILE:SetReductionTest> PROCESSES 27 )



waLBerla_compile_test( FILES mpi/ProbeVsExtraMessage.cpp )


##############
# ptrvector #
##############

waLBerla_compile_test( NAME PtrVector FILES ptrvector/PtrVector.cpp )
waLBerla_execute_test( NAME PtrVector )

##############
# selectable #
##############

waLBerla_compile_test( FILES selectable/SetSelectableObjectTest.cpp )
waLBerla_execute_test( NAME SetSelectableObjectTest  )

##########
# timing #
##########

waLBerla_compile_test( FILES timing/TimerTest.cpp )
waLBerla_execute_test( NAME TimerTest )

waLBerla_compile_test( FILES timing/TimingPoolTest.cpp )
waLBerla_execute_test( NAME TimingPoolTest PROCESSES 3  )

waLBerla_compile_test( FILES timing/TimingTreeTest.cpp )
waLBerla_execute_test( NAME TimingTreeTest PROCESSES 3)

waLBerla_compile_test( FILES timing/SweepTimeloopTimerReduction.cpp DEPENDS timeloop blockforest )
waLBerla_execute_test( NAME SweepTimeloopTimerReduction PROCESSES 9  )


########
# core #
########

waLBerla_compile_test( FILES AllHeaderTest.cpp DEPENDS blockforest field geometry pe pe_coupling python_coupling )
waLBerla_execute_test( NAME AllHeaderTest )

waLBerla_compile_test( FILES ConcatIterator.cpp )
waLBerla_execute_test( NAME ConcatIterator )

waLBerla_compile_test( FILES DataTypesTest.cpp )
waLBerla_execute_test( NAME DataTypesTest )

waLBerla_compile_test( FILES GridGeneratorTest.cpp )
waLBerla_execute_test( NAME GridGeneratorTest )

waLBerla_compile_test( FILES SetTest.cpp )
waLBerla_execute_test( NAME SetTest )

waLBerla_compile_test( NAME UNIQUEID FILES UniqueID.cpp )
waLBerla_execute_test( NAME UNIQUEID PROCESSES 4)

waLBerla_compile_test( FILES VersionTest.cpp )
waLBerla_execute_test( NAME VersionTest )
