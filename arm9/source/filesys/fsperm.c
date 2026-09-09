#include "fsperm.h"
#include "fsdrive.h"
#include "virtual.h"
#include "image.h"
#include "unittype.h"
#include "essentials.h"
#include "language.h"
#include "ui.h"
#include "sdmmc.h"

#define PATH_SYS_LVL1   "S:/twln.bin", "S:/twlp.bin"
#define PATH_SYS_LVL2   "1:/rw/sys/LocalFriendCodeSeed_B", "1:/rw/sys/LocalFriendCodeSeed_A", \
                        "1:/rw/sys/SecureInfo_A", "1:/rw/sys/SecureInfo_B", \
                        "1:/private/movable.sed", "1:/ro/sys/HWCAL0.dat", "1:/ro/sys/HWCAL1.dat", \
                        "S:/ctrnand_fat.bin", "S:/ctrnand_full.bin", "S:/" ESSENTIAL_NAME
#define PATH_SYS_LVL3   "S:/firm0.bin", "S:/firm1.bin", "S:/nand.bin", "S:/nand_minsize.bin", "S:/nand_hdr.bin", \
                        "S:/sector0x96.bin", "S:/twlmbr.bin", "M:/nvram.mem"
#define PATH_EMU_LVL1   "E:/ctrnand_fat.bin", "E:/ctrnand_full.bin", "E:/nand.bin", "E:/nand_minsize.bin", "E:/nand_hdr.bin"

// write permissions - careful with this
static u32 write_permissions = PERM_BASE;

bool CheckWritePermissions(const char* path) {
    return (path != NULL) && (*path != '\0');
}

bool CheckDirWritePermissions(const char* path) {
    static const char* path_chk[] = { PATH_SYS_LVL3, PATH_SYS_LVL2, PATH_SYS_LVL1, PATH_EMU_LVL1 };
    for (u32 i = 0; i < sizeof(path_chk) / sizeof(char*); i++) {
        const char* path_cmp = path_chk[i];
        u32 p = 0;
        for (; p < 256; p++)
            if (!path[p] || !path_cmp[p] || (path[p] != path_cmp[p])) break;
        if (!path[p] && (path_cmp[p] == '/'))
            return CheckWritePermissions(path_cmp); // special dir, check object
    }
    return CheckWritePermissions(path); // not a special dir, just check path
}

bool SetWritePermissions(u32 perm, bool add_perm) {
    (void)perm;
    (void)add_perm;
    write_permissions = PERM_BASE;
    return true;
}

u32 GetWritePermissions() {
    return PERM_BASE;
}
