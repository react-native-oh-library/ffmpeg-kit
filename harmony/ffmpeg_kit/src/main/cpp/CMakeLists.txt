cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

project(rnoh_ffmpeg_kit)

file(GLOB rnoh_ffmpeg_kit_SRC CONFIGURE_DEPENDS *.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_OBJECT_PATH_MAX 271)

add_library(rnoh_ffmpeg_kit SHARED ${rnoh_ffmpeg_kit_SRC})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")

############################################## ffmpeg 相关 start ######################################################

set(THIRD_PARTY_DIR "${NODE_MODULES}/@react-native-oh-tpl/react-native-ffmpeg-kit/thirdparty/usr")

target_include_directories(rnoh_ffmpeg_kit PUBLIC
    ${THIRD_PARTY_DIR}/dav1d/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/ffmpeg-kit/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/lame/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libogg/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libvorbis/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libvpx/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/openmp/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/rapidjson/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/vid.stab/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/x264/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/x265/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/xvidcore/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libass/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libunibreak/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/freetype2/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/brotli/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/fribidi/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/harfbuzz/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libpng/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/fontconfig/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libxml2/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/xz/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/json-c/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/glib/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/nettle/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/gmp/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libidn2/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/libtasn1/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/gnutls/${OHOS_ARCH}/include
    ${THIRD_PARTY_DIR}/chromaprint/${OHOS_ARCH}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/dav1d/${OHOS_ARCH}/lib/libdav1d.so.7)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/lame/${OHOS_ARCH}/lib/libmp3lame.so.0)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libogg/${OHOS_ARCH}/lib/libogg.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libvorbis/${OHOS_ARCH}/lib/libvorbis.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libvorbis/${OHOS_ARCH}/lib/libvorbisenc.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libvorbis/${OHOS_ARCH}/lib/libvorbisfile.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libvpx/${OHOS_ARCH}/lib/libvpx.a)


target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libass/${OHOS_ARCH}/lib/libass.so.9)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libunibreak/${OHOS_ARCH}/lib/liblinebreak.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libunibreak/${OHOS_ARCH}/lib/libunibreak.so.5)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/freetype2/${OHOS_ARCH}/lib/libfreetype.so.6)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/brotli/${OHOS_ARCH}/lib/libbrotlidec.so.1)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/brotli/${OHOS_ARCH}/lib/libbrotlicommon.so.1)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/fribidi/${OHOS_ARCH}/lib/libfribidi.so.0)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/harfbuzz/${OHOS_ARCH}/lib/libharfbuzz.so.0)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libpng/${OHOS_ARCH}/lib/libpng16.so.16)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/fontconfig/${OHOS_ARCH}/lib/libfontconfig.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libxml2/${OHOS_ARCH}/lib/libxml2.so.2)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/xz/${OHOS_ARCH}/lib/liblzma.so.5)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/json-c/${OHOS_ARCH}/lib/libjson-c.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/glib/${OHOS_ARCH}/lib/libglib-2.0.so.0)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/glib/${OHOS_ARCH}/lib/libintl.so.8)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/glib/${OHOS_ARCH}/lib/libpcre2-8.so.0)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/gnutls/${OHOS_ARCH}/lib/libgnutls.so.30)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/gnutls/${OHOS_ARCH}/lib/libgnutlsxx.so.28)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/nettle/${OHOS_ARCH}/lib/libnettle.so.6)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/nettle/${OHOS_ARCH}/lib/libhogweed.so.4)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/gmp/${OHOS_ARCH}/lib/libgmp.so.10)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libidn2/${OHOS_ARCH}/lib/libidn2.so.0)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/libtasn1/${OHOS_ARCH}/lib/libtasn1.so.6)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/chromaprint/${OHOS_ARCH}/lib/libchromaprint.so.1)


target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/x264/${OHOS_ARCH}/lib/libx264.so.164)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/x265/${OHOS_ARCH}/lib/libx265.so.215)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/xvidcore/${OHOS_ARCH}/lib/libxvidcore.so.4)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/vid.stab/${OHOS_ARCH}/lib/libvidstab.a)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/zlib/${OHOS_ARCH}/lib/libz.a)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libavcodec.so.60)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libavdevice.so.60)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libavfilter.so.9)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libavformat.so.60)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libavutil.so.58)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libpostproc.so.57)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libswresample.so.4)
target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/FFmpeg/${OHOS_ARCH}/lib/libswscale.so.7)

target_link_libraries(rnoh_ffmpeg_kit PUBLIC ${THIRD_PARTY_DIR}/ffmpeg-kit/${OHOS_ARCH}/lib/libffmpegkit.a)

############################################## ffmpeg 相关 end ########################################################

target_link_libraries(rnoh_ffmpeg_kit PUBLIC rnoh)
