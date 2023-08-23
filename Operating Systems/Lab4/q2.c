#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<time.h>
int main (int argc, char *argv[])
{
    struct stat sb;
    int ret;
    if (argc < 2) 
    {
        fprintf (stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }
    ret = stat (argv[1], &sb);
    if (ret) 
    {
        perror ("stat");
        return 1;
    }
    printf ("%s has device no.: %ld \n", argv[1], sb.st_dev);
    printf ("%s has inode no.: %ld \n", argv[1], sb.st_ino);
    printf ("%s has mode: %d \n", argv[1], sb.st_mode);
    printf ("%s has %ld  no. of hard links\n", argv[1], sb.st_nlink);
    printf ("%s has userid of owner: %d \n", argv[1], sb.st_uid);
    printf ("%s has grpid of owner: %d \n", argv[1], sb.st_gid);
    printf ("%s has device id(if special file): %ld \n", argv[1], sb.st_rdev);
    printf ("%s has size: %ld bytes\n", argv[1], sb.st_size);
    printf ("%s has block size: %ld bytes\n", argv[1], sb.st_blksize);
    printf ("%s has %ld blocks allocated\n", argv[1], sb.st_blocks);
    printf ("%s has last access time:%s\n", argv[1], ctime(&sb.st_atime));
    printf ("%s has last modification time:%s\n", argv[1], ctime(&sb.st_mtime));
    printf ("%s has last status change time:%s\n", argv[1], ctime(&sb.st_ctime));

    return 0;
}
// struct stat {
// dev_t st_dev; /* ID of device containing file */
// ino_t st_ino; /* inode number */
// mode_t st_mode; /* permissions */
// nlink_t st_nlink; /* number of hard links */
// uid_t st_uid; /* user ID of owner */
// gid_t st_gid; /* group ID of owner */
// dev_t st_rdev; /* device ID (if special file) */
// off_t st_size; /* total size in bytes */
// blksize_t st_blksize; /* blocksize for filesystem I/O */
// blkcnt_t st_blocks; /* number of blocks allocated */
// time_t st_atime; /* last access time */
// time_t st_mtime; /* last modification time */
// time_t st_ctime; /* last status change time */
// };