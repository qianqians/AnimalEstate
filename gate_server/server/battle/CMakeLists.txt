PROJECT(battle)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0) 

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(abseil_INCLUDE_PATH ../../3rdparty/abseil-cpp CACHE PATH "abseil include path")
INCLUDE_DIRECTORIES(${abseil_INCLUDE_PATH})

set(mimalloc_INCLUDE_PATH ../../3rdparty/mimalloc/include CACHE PATH "mimalloc include path")
INCLUDE_DIRECTORIES(${mimalloc_INCLUDE_PATH})

set(crossguid_INCLUDE_PATH ../../3rdparty/crossguid/include CACHE PATH "crossguid include path")
INCLUDE_DIRECTORIES(${crossguid_INCLUDE_PATH})

set(spdlog_INCLUDE_PATH ../../3rdparty/spdlog/include CACHE PATH "spdlog include path")
INCLUDE_DIRECTORIES(${spdlog_INCLUDE_PATH})

set(json11_INCLUDE_PATH ../../3rdparty/json11 CACHE PATH "json11 include path")
INCLUDE_DIRECTORIES(${json11_INCLUDE_PATH})

set(libbson_INCLUDE_PATH ../../3rdparty/libbson/include CACHE PATH "libbson include path")
INCLUDE_DIRECTORIES(${libbson_INCLUDE_PATH})

set(msgpack11_INCLUDE_PATH ../../juggle/3rdparty/msgpack11 CACHE PATH "msgpack11 include path")
INCLUDE_DIRECTORIES(${msgpack11_INCLUDE_PATH})

set(concurrent_INCLUDE_PATH ../../juggle/concurrent CACHE PATH "concurrent include path")
INCLUDE_DIRECTORIES(${concurrent_INCLUDE_PATH})

set(juggle_header_path ../../juggle/ CACHE PATH "juggle include path")
INCLUDE_DIRECTORIES(${juggle_header_path})

set(proto_header_path ./proto/ CACHE PATH "proto include path")
INCLUDE_DIRECTORIES(${proto_header_path})

set(time_header_path ../../time CACHE PATH "time include path")
INCLUDE_DIRECTORIES(${time_header_path})

set(config_header_path ../../config CACHE PATH "config include path")
INCLUDE_DIRECTORIES(${config_header_path})

set(service_header_path ../../service CACHE PATH "service include path")
INCLUDE_DIRECTORIES(${service_header_path})

set(module_header_path ../../module CACHE PATH "module include path")
INCLUDE_DIRECTORIES(${module_header_path})

set(log_header_path ../../log CACHE PATH "log include path")
INCLUDE_DIRECTORIES(${log_header_path})

set(protocol_header_path ../../framework_proto CACHE PATH "protocol include path")
INCLUDE_DIRECTORIES(${protocol_header_path})

set(hub_header_path ../../component/hub CACHE PATH "hub include path")
INCLUDE_DIRECTORIES(${hub_header_path})

file(GLOB def_header_files ./ ./*.h)
file(GLOB msg_handle_header_files ./msg_handle/ ./msg_handle/*.h)
file(GLOB battle_header_files ./battle/ ./battle/*.h)
file(GLOB json_config_header_files ./json_config/ ./json_config/*.h)

AUX_SOURCE_DIRECTORY(./battle/ battle_DIR_SRC)
AUX_SOURCE_DIRECTORY(./json_config/ json_config_DIR_SRC)

file(GLOB proto_header_files ./proto/ ./proto/*.h)
AUX_SOURCE_DIRECTORY(./proto/ proto_DIR_SRC)

AUX_SOURCE_DIRECTORY(. DIR_SRC)
file(GLOB header_test_files ./ ./*.h)

set(WINDOWS_LIBS_DEBUG_PATH ${PROJECT_SOURCE_DIR}//..//lib_debug CACHE PATH "windows lib debug path")
set(WINDOWS_LIBS_RELEASE_PATH ${PROJECT_SOURCE_DIR}//..//lib CACHE PATH "windows lib release path")

SET(header_files
	${def_header_files}
	${msg_handle_header_files}
	${battle_header_files}
	${json_config_header_files}
    ${header_test_files}
    ${proto_header_files}
)

SET(SRC_LIST 
	${battle_DIR_SRC}
	${json_config_DIR_SRC}
    ${DIR_SRC}
    ${proto_DIR_SRC}
)

ADD_EXECUTABLE(battle ${SRC_LIST} ${header_files})
if (CMAKE_HOST_WIN32)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/libssl64MDd.lib optimized ${LIBS_RELEASE_PATH}/libssl64MD.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/hiredis.lib optimized ${LIBS_RELEASE_PATH}/hiredis.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/hiredis_cluster.lib optimized ${LIBS_RELEASE_PATH}/hiredis_cluster.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/crossguid-dgb.lib optimized ${LIBS_RELEASE_PATH}/crossguid.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/libcrypto64MDd.lib optimized ${LIBS_RELEASE_PATH}/libcrypto64MD.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/spdlogd.lib optimized ${LIBS_RELEASE_PATH}/spdlog.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/enet.lib optimized ${LIBS_RELEASE_PATH}/enet.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/msgpack11.lib optimized ${LIBS_RELEASE_PATH}/msgpack11.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/json11.lib optimized ${LIBS_RELEASE_PATH}/json11.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/cares.lib optimized ${LIBS_RELEASE_PATH}/cares.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/bson.lib optimized ${LIBS_RELEASE_PATH}/bson.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/mimalloc-static.lib optimized ${LIBS_RELEASE_PATH}/mimalloc-static.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/absl_city.lib optimized ${LIBS_RELEASE_PATH}/absl_city.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/absl_hash.lib optimized ${LIBS_RELEASE_PATH}/absl_hash.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/absl_wyhash.lib optimized ${LIBS_RELEASE_PATH}/absl_wyhash.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/absl_raw_hash_set.lib optimized ${LIBS_RELEASE_PATH}/absl_raw_hash_set.lib)
	target_link_libraries(battle debug ${LIBS_DEBUG_PATH}/hub.lib optimized ${LIBS_RELEASE_PATH}/hub.lib)
	target_link_libraries(battle Crypt32 )
	target_link_libraries(battle ws2_32)
	target_link_libraries(battle winmm)
endif ()