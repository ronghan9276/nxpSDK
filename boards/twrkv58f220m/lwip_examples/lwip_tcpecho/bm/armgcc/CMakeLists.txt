INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mcpu=cortex-m7")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mfpu=fpv5-sp-d16")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_INITIALIZE_NONCACHEDATA")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m7")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mfpu=fpv5-sp-d16")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_MKV58F1M0VLQ24")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTWR_KV58F220M")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTOWER")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSERIAL_PORT_TYPE_UART=1")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mcpu=cortex-m7")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mfpu=fpv5-sp-d16")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_MKV58F1M0VLQ24")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DTWR_KV58F220M")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DTOWER")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSERIAL_PORT_TYPE_UART=1")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mcpu=cortex-m7")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mfpu=fpv5-sp-d16")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSERIAL_PORT_TYPE_UART=1")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mcpu=cortex-m7")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mfpu=fpv5-sp-d16")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mthumb")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MMD")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-common")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mapcs")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-rtti")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DSERIAL_PORT_TYPE_UART=1")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mcpu=cortex-m7")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mfpu=fpv5-sp-d16")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mthumb")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MMD")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-common")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mapcs")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-exceptions")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mcpu=cortex-m7")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mfpu=fpv5-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nosys.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Map=output.map")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=__stack_size__=0x1000")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=__heap_size__=0x1000")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mcpu=cortex-m7")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfloat-abi=hard")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mfpu=fpv5-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nosys.specs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -z")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Map=output.map")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=__stack_size__=0x1000")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=__heap_size__=0x1000")

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../../..)

include_directories(${ProjDirPath}/../../../../../../CMSIS/Include)

include_directories(${ProjDirPath}/../../../../../../devices)

include_directories(${ProjDirPath}/../../../../../../components/phy/mdio/enet)

include_directories(${ProjDirPath}/../../../../../../components/phy/device/phyksz8041)

include_directories(${ProjDirPath}/../../../../../../middleware/lwip/contrib/apps/tcpecho_raw)

include_directories(${ProjDirPath}/../../../../../../middleware/lwip/port)

include_directories(${ProjDirPath}/../../../../../../middleware/lwip/src)

include_directories(${ProjDirPath}/../../../../../../middleware/lwip/src/include)

include_directories(${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/str)

include_directories(${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/debug_console)

include_directories(${ProjDirPath}/../../../../../../devices/MKV58F24/drivers)

include_directories(${ProjDirPath}/../../../../../../devices/MKV58F24)

include_directories(${ProjDirPath}/../../../../../../components/uart)

include_directories(${ProjDirPath}/../../../../../../components/serial_manager)

include_directories(${ProjDirPath}/../../../../../../components/lists)

include_directories(${ProjDirPath}/../../../../../../components/phy)

include_directories(${ProjDirPath}/../../../../../../devices/MKV58F24/utilities)

add_executable(lwip_tcpecho_bm.elf 
"${ProjDirPath}/../lwip_tcpecho_bm.c"
"${ProjDirPath}/../lwipopts.h"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../../../../../../components/phy/mdio/enet/fsl_enet_mdio.c"
"${ProjDirPath}/../../../../../../components/phy/mdio/enet/fsl_enet_mdio.h"
"${ProjDirPath}/../../../../../../components/phy/device/phyksz8041/fsl_phyksz8041.c"
"${ProjDirPath}/../../../../../../components/phy/device/phyksz8041/fsl_phyksz8041.h"
"${ProjDirPath}/../../../../../../middleware/lwip/contrib/apps/tcpecho_raw/tcpecho_raw.c"
"${ProjDirPath}/../../../../../../middleware/lwip/contrib/apps/tcpecho_raw/tcpecho_raw.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/arch/cc.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/arch/perf.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/arch/sys_arch.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/sys_arch.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/api_lib.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/api_msg.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/err.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/if_api.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/netbuf.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/netdb.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/netifapi.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/sockets.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/api/tcpip.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/altcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/altcp_alloc.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/altcp_tcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/def.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/dns.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/inet_chksum.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/init.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ip.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/acd.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/autoip.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/dhcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/etharp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/icmp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/igmp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/ip4.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/ip4_addr.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv4/ip4_frag.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/dhcp6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/ethip6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/icmp6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/inet6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/ip6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/ip6_addr.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/ip6_frag.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/mld6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/ipv6/nd6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/mem.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/memp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/netif.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/pbuf.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/raw.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/stats.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/sys.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/tcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/tcp_in.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/tcp_out.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/timeouts.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/core/udp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/compat/posix/arpa/inet.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/compat/posix/net/if.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/compat/posix/netdb.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/compat/posix/sys/socket.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/compat/stdc/errno.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/acd.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/altcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/altcp_tcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/altcp_tls.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/api.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/arch.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/autoip.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/debug.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/def.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/dhcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/dhcp6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/dns.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/err.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/errno.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/etharp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ethip6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/icmp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/icmp6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/if_api.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/igmp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/inet.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/inet_chksum.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/init.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip4.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip4_addr.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip4_frag.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip6_addr.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip6_frag.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip6_zone.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/ip_addr.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/mem.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/memp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/mld6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/nd6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/netbuf.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/netdb.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/netif.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/netifapi.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/opt.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/pbuf.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/altcp_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/api_msg.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/mem_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/memp_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/memp_std.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/nd6_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/raw_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/sockets_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/tcp_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/priv/tcpip_priv.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/acd.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/autoip.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/dhcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/dhcp6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/dns.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/etharp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/ethernet.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/iana.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/icmp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/icmp6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/ieee.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/igmp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/ip.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/ip4.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/ip6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/mld6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/nd6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/tcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/prot/udp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/raw.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/sio.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/snmp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/sockets.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/stats.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/sys.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/tcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/tcpbase.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/tcpip.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/timeouts.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/lwip/udp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/bridgeif.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/bridgeif_opts.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/etharp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ethernet.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ieee802154.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/lowpan6.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/lowpan6_ble.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/lowpan6_common.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/lowpan6_opts.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ccp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/chap-md5.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/chap-new.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/chap_ms.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/eap.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ecp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/eui64.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/fsm.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ipcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ipv6cp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/lcp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/magic.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/mppe.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/polarssl/arc4.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/polarssl/des.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/polarssl/md4.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/polarssl/md5.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/polarssl/sha1.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ppp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ppp_impl.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/ppp_opts.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppapi.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppcrypt.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppdebug.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppoe.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppol2tp.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/pppos.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/upap.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/ppp/vj.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/slipif.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/include/netif/zepif.h"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/bridgeif.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/bridgeif_fdb.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ethernet.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/lowpan6.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/lowpan6_ble.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/lowpan6_common.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/auth.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/ccp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/chap-md5.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/chap-new.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/chap_ms.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/demand.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/eap.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/eui64.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/fsm.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/ipcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/ipv6cp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/lcp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/lwip_ecp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/magic.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/mppe.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/multilink.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/ppp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/pppapi.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/pppcrypt.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/pppoe.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/pppol2tp.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/pppos.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/upap.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/utils.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/ppp/vj.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/slipif.c"
"${ProjDirPath}/../../../../../../middleware/lwip/src/netif/zepif.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/debug_console/fsl_debug_console.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/debug_console/fsl_debug_console.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/debug_console/fsl_debug_console_conf.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/str/fsl_str.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/str/fsl_str.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/enet_ethernetif.c"
"${ProjDirPath}/../../../../../../middleware/lwip/port/enet_ethernetif.h"
"${ProjDirPath}/../../../../../../middleware/lwip/port/enet_ethernetif_kinetis.c"
"${ProjDirPath}/../../../../../../middleware/lwip/port/enet_ethernetif_priv.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_port.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_sim.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_sim.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_clock.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_clock.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_common.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_common.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/MKV58F24.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/MKV58F24_features.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/fsl_device_registers.h"
"${ProjDirPath}/../../../../../../components/uart/uart.h"
"${ProjDirPath}/../../../../../../components/uart/uart_adapter.c"
"${ProjDirPath}/../../../../../../components/serial_manager/serial_manager.c"
"${ProjDirPath}/../../../../../../components/serial_manager/serial_manager.h"
"${ProjDirPath}/../../../../../../components/serial_manager/serial_port_internal.h"
"${ProjDirPath}/../../../../../../components/lists/generic_list.c"
"${ProjDirPath}/../../../../../../components/lists/generic_list.h"
"${ProjDirPath}/../../../../../../components/serial_manager/serial_port_uart.c"
"${ProjDirPath}/../../../../../../components/serial_manager/serial_port_uart.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_uart.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_uart.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/gcc/startup_MKV58F24.S"
"${ProjDirPath}/../../../../../../devices/MKV58F24/system_MKV58F24.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/system_MKV58F24.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_smc.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_smc.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_gpio.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_gpio.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/fsl_assert.c"
"${ProjDirPath}/../../../../../../components/phy/fsl_mdio.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/core_cm7.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/mpu_armv7.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_armcc.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_armclang.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_armclang_ltm.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_compiler.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_gcc.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_iccarm.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/cmsis_version.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/arm_common_tables.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/arm_const_structs.h"
"${ProjDirPath}/../../../../../../CMSIS/Include/arm_math.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_enet.c"
"${ProjDirPath}/../../../../../../devices/MKV58F24/drivers/fsl_enet.h"
"${ProjDirPath}/../../../../../../components/phy/fsl_phy.h"
"${ProjDirPath}/../../../../../../devices/MKV58F24/utilities/fsl_sbrk.c"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/MKV58F1M0xxx24_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/MKV58F1M0xxx24_flash.ld -static")

TARGET_LINK_LIBRARIES(lwip_tcpecho_bm.elf -Wl,--start-group)
target_link_libraries(lwip_tcpecho_bm.elf debug m)

target_link_libraries(lwip_tcpecho_bm.elf debug c)

target_link_libraries(lwip_tcpecho_bm.elf debug gcc)

target_link_libraries(lwip_tcpecho_bm.elf debug nosys)

target_link_libraries(lwip_tcpecho_bm.elf optimized m)

target_link_libraries(lwip_tcpecho_bm.elf optimized c)

target_link_libraries(lwip_tcpecho_bm.elf optimized gcc)

target_link_libraries(lwip_tcpecho_bm.elf optimized nosys)

TARGET_LINK_LIBRARIES(lwip_tcpecho_bm.elf -Wl,--end-group)


