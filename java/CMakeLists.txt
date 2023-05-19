# 3.11+ is required to use add_jar
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# make sure it works with OpenJDK
set(JAVA_AWT_LIBRARY NotNeeded)
set(JAVA_JVM_LIBRARY NotNeeded)

find_package(JNI REQUIRED)
find_package(Java)
include(UseJava)

# This jar is just to make use of the GENERATE_NATIVE_HEADERS functionality.
# The vw980_jni_generate_native_headers_do_not_use_jar.jar itself should not be used in any way.
add_jar(vw980_jni_generate_native_headers_do_not_use_jar
SOURCES
  src/main/java/vw980/common/Native.java
  src/main/java/vw980/org/vowpalwabbit/spark/ClusterSpanningTree.java
  src/main/java/vw980/org/vowpalwabbit/spark/prediction
  src/main/java/vw980/org/vowpalwabbit/spark/prediction/ScalarPrediction.java
  src/main/java/vw980/org/vowpalwabbit/spark/VowpalWabbitArguments.java
  src/main/java/vw980/org/vowpalwabbit/spark/VowpalWabbitExample.java
  src/main/java/vw980/org/vowpalwabbit/spark/VowpalWabbitMurmur.java
  src/main/java/vw980/org/vowpalwabbit/spark/VowpalWabbitNative.java
  src/main/java/vw980/org/vowpalwabbit/spark/VowpalWabbitPerformanceStatistics.java
  src/main/java/vw980/vowpalWabbit/learner/package-info.java
  src/main/java/vw980/vowpalWabbit/learner/VWActionProbsLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWActionScoresLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWBase.java
  src/main/java/vw980/vowpalWabbit/learner/VWCCBLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWFloatLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWIntLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWLearnerBase.java
  src/main/java/vw980/vowpalWabbit/learner/VWLearners.java
  src/main/java/vw980/vowpalWabbit/learner/VWMulticlassLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWMultilabelsLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWProbLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWScalarLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWScalarsLearner.java
  src/main/java/vw980/vowpalWabbit/learner/VWTypedLearner.java
  src/main/java/vw980/vowpalWabbit/responses/ActionProb.java
  src/main/java/vw980/vowpalWabbit/responses/ActionProbs.java
  src/main/java/vw980/vowpalWabbit/responses/ActionScore.java
  src/main/java/vw980/vowpalWabbit/responses/ActionScores.java
  src/main/java/vw980/vowpalWabbit/responses/DecisionScores.java
  src/main/java/vw980/vowpalWabbit/responses/Multilabels.java
  src/main/java/vw980/vowpalWabbit/responses/PDF.java
  src/main/java/vw980/vowpalWabbit/responses/PDFSegment.java
  src/main/java/vw980/vowpalWabbit/responses/PDFValue.java
  src/main/java/vw980/vowpalWabbit/VW.java
GENERATE_NATIVE_HEADERS vw980_jni_native_headers)

set(src_base src/main/c++)
set(vw980_jni_headers
  ${src_base}/jni_base_learner.h
  ${src_base}/vowpalWabbit_VW.h
  ${src_base}/jni_spark_vw.h
  ${src_base}/util.h
)

set(vw980_jni_sources
  ${src_base}/jni_base_learner.cc
  ${src_base}/vowpalWabbit_learner_VWCCBLearner.cc
  ${src_base}/vowpalWabbit_learner_VWActionProbsLearner.cc
  ${src_base}/vowpalWabbit_learner_VWActionScoresLearner.cc
  ${src_base}/vowpalWabbit_learner_VWLearners.cc
  ${src_base}/vowpalWabbit_learner_VWMulticlassLearner.cc
  ${src_base}/vowpalWabbit_learner_VWMultilabelsLearner.cc
  ${src_base}/vowpalWabbit_learner_VWProbLearner.cc
  ${src_base}/vowpalWabbit_learner_VWScalarLearner.cc
  ${src_base}/vowpalWabbit_learner_VWScalarsLearner.cc
  ${src_base}/vowpalWabbit_VW.cc
  ${src_base}/jni_spark_vw.cc
  ${src_base}/jni_spark_cluster.cc
  ${src_base}/util.cc
)

add_library(vw980_jni SHARED ${vw980_jni_headers} ${vw980_jni_sources})
target_link_libraries(vw980_jni
  PUBLIC vw_core vw_spanning_tree
  PRIVATE vw980_jni_native_headers
)
set_property(TARGET vw980_jni PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET vw980_jni PROPERTY BUILD_RPATH_USE_ORIGIN ON)
target_include_directories(vw980_jni PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${JNI_INCLUDE_DIRS})

# Ensure target directory exists
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/target/bin/natives/linux_64/)
add_custom_command(TARGET vw980_jni POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:vw980_jni> ${CMAKE_CURRENT_SOURCE_DIR}/target/bin/natives/linux_64/
)

if(${CMAKE_EXECUTABLE_FORMAT} MATCHES "ELF")
  # enable-new-dtags and rpath enables shared object library lookup in the location of libvw_spark_jni.so
  # dtags are an ELF feature
  target_link_libraries(vw980_jni PUBLIC -Wl,--enable-new-dtags)
endif()

# Replace version number in POM
configure_file(pom.xml.in ${CMAKE_CURRENT_SOURCE_DIR}/pom.xml @ONLY)

if(NOT WIN32)
  # Ensure target directory exists
  file(MAKE_DIRECTORY target/classes)
  file(MAKE_DIRECTORY target/test-classes)
  file(MAKE_DIRECTORY target/bin/natives/linux_64)

  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(JAVA_INSTALL_PATH /Library/Java/Extensions)
  else()
    set(JAVA_INSTALL_PATH /usr/lib)
  endif()

  add_custom_command(TARGET vw980_jni POST_BUILD
      COMMAND cp $<TARGET_FILE:vw980_jni> target/bin/natives/linux_64
      COMMAND echo $<TARGET_FILE:vw_cli_bin> > ${CMAKE_CURRENT_SOURCE_DIR}/target/test-classes/vw_cli_bin.txt
      # -B is batch mode and avoids the massive download progress print out
      COMMAND mvn -B verify
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Copying shared libary dependencies to output directory")

  # Replace version number in POM
  configure_file(pom.xml.in ${CMAKE_CURRENT_SOURCE_DIR}/pom.xml @ONLY)

  if(VW_INSTALL)
      install(TARGETS vw980_jni
      RUNTIME DESTINATION ${JAVA_INSTALL_PATH}
      LIBRARY DESTINATION ${JAVA_INSTALL_PATH}
      )
  endif()

endif()
