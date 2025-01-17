cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

project(rnoh_ffmpeg_kit)

file(GLOB rnoh_ffmpeg_kit_SRC CONFIGURE_DEPENDS *.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(rnoh_ffmpeg_kit SHARED ${rnoh_ffmpeg_kit_SRC})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")

############################################## ffmpeg 相关 start ######################################################

set(THIRD_PARTY_DIR "${NODE_MODULES}/@react-native-oh-tpl/react-native-ffmpeg-kit")

target_include_directories(rnoh_ffmpeg_kit PUBLIC
    ${THIRD_PARTY_DIR}/thirdparty/FFmpeg-kit/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/dav1d/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/lame/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/libogg/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/libvorbis/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/libvpx/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/openh264/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/openssl_1_0_2u/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/rapidjson/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/rtmpdump/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/thirdparty/zlib/${OHOS_ARCH}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/dav1d/${OHOS_ARCH}/lib/libdav1d.so.7)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/lame/${OHOS_ARCH}/lib/libmp3lame.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/libogg/${OHOS_ARCH}/lib/libogg.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/libvorbis/${OHOS_ARCH}/lib/libvorbis.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/libvorbis/${OHOS_ARCH}/lib/libvorbisenc.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/libvorbis/${OHOS_ARCH}/lib/libvorbisfile.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/libvpx/${OHOS_ARCH}/lib/libvpx.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/openh264/${OHOS_ARCH}/lib/libopenh264.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/openssl_1_0_2u/${OHOS_ARCH}/lib/libcrypto.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/openssl_1_0_2u/${OHOS_ARCH}/lib/libssl.a)


#target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/rtmpdump/${OHOS_ARCH}/lib/librtmp.a)
add_library(librtmp STATIC IMPORTED)
set_target_properties(librtmp PROPERTIES IMPORTED_LOCATION ${THIRD_PARTY_DIR}/thirdparty/rtmpdump/${OHOS_ARCH}/lib/librtmp.a)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/zlib/${OHOS_ARCH}/lib/libz.a)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libavcodec.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libavdevice.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libavfilter.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libavformat.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libavutil.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libswresample.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg/${OHOS_ARCH}/lib/libswscale.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/thirdparty/FFmpeg-kit/${OHOS_ARCH}/lib/libffmpegkit.a)




############################################## ffmpeg 相关 end ########################################################


target_link_libraries(rnoh_ffmpeg_kit PUBLIC librtmp)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC rnoh)
