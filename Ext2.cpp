#include "Ext2.h"

std::string convertDateTime(int ttc){

    //Calculating the date based on the given value
    struct tm ts;
    char string[100];
    time_t time_to_convert = (time_t)ttc;
    ts = *localtime(&time_to_convert);
    strftime(string, sizeof(string), "%a %b %d %H:%M:%S %Y", &ts);

    return std::string(string);
}


void Ext2::printData()
{
    int blocksize = 1024 << this->blocksize;
    std::string last_checked = convertDateTime(this->lastcheck);
    std::string last_mount = convertDateTime(this->lastmount);
    std::string last_write = convertDateTime(this->lastwrite);

    std::cout << FILESYSTEM_PRINT << endl;
    std::cout << FILESYSTEM_TYPE << "Ext2" << endl;
    std::cout << INODE_INFO << endl;
    std::cout << INODE_SIZE << this->inodesize << endl;
    std::cout << INODE_NUM << this->toatlnuminodes << endl;
    std::cout << INODE_FIRST << this->firstinode << endl;
    std::cout << INODE_GROUP << this->inodespergroup << endl;
    std::cout << INODE_FREE << this->freeinode << endl;
    std::cout << "\n" << BLOCK_INFO << endl;
    std::cout << BLOCK_RESERVED << this->reservedblock << endl;
    std::cout << BLOCK_SIZE << blocksize << endl;
    std::cout << BLOCK_FREE << this->freeblock << endl;
    std::cout << BLOCK_TOTAL << this->totalblock << endl;
    std::cout << BLOCK_FIRST << this->firstblock << endl;
    std::cout << BLOCK_GROUP << this->groupblock << endl;
    std::cout << BLOCK_FRAG << this->fraggroup << endl;
    std::cout << "\n" << VOLUME_INFO << endl;
    std::cout << VOLUME_NAME << this->volume_name << endl;
    std::cout << VOLUME_CHECK << last_checked << endl;
    std::cout << VOLUME_LAST << last_mount << endl;
    std::cout << VOLUME_WRITE << last_write << endl;

    /*
    struct tm ts;
    char buf[80];

    // Get current time
    time(&this->lastwrite);

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&this->lastwrite);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    printf("%s\n", buf);

    //printf("%s", ctime());
    
    */
}
void Ext2::setData()
{

    cout << "We're setting Ext2 data" << endl;
}