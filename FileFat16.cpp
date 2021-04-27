#include "FileFat16.h"

Fat16 FileFat16::putFileInfoOnObjectFat16(char *filename)
{
    Fat16 fat16;

    FILE *file;
    int i;

    file = fopen(filename, "r");

    fseek(file, BS_OEMNAME_OFFSET, SEEK_SET);
    fread((void *)(fat16.system_name), sizeof(char), BS_OEMNAME_BYTES, file);

    rewind(file);
    fflush(0);

    fseek(file, BPB_BYTSPERSEC_OFFSET, SEEK_SET);
    fread(&fat16.sector_size, sizeof(short), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BPB_SECPERCLUS_OFFSET, SEEK_SET);
    fread(&fat16.sectors_per_cluster, sizeof(char), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BPB_RSVDSECCNT, SEEK_SET);
    fread(&fat16.reserved_sec, sizeof(short), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BPB_NUMFATS_OFFSET, SEEK_SET);
    fread(&fat16.fat_num, sizeof(char), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    fread(&fat16.max_root, sizeof(short), 1, file);
    rewind(file);
    fflush(0);

    fseek(file, OFFSET_FAT16, SEEK_SET);
    fread(&fat16.sectors_per_fat, sizeof(short), 1, file);

    rewind(file);
    fflush(0);

    fseek(file, BS_VOLLAB_OFFSET, SEEK_SET);
    fread((void *)(fat16.volume_label), sizeof(char), BS_VOLLAB_BYTES, file);
    fclose(file);

    return fat16;
}
