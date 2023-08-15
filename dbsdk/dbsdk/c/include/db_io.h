#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define IO_WHENCE_BEGIN 0
#define IO_WHENCE_CURRENT 1
#define IO_WHENCE_END 2

#define IO_FILEMODE_READ 0
#define IO_FILEMODE_WRITE 1

/// @brief Directory entry detailing information about a file or directory
typedef struct
{
    /// @brief The name of the file or directory
    char name[128];

    /// @brief A timestamp representing the time this file or directory was created
    uint64_t created;

    /// @brief A timestamp representing the time this file or directory was last modified
    uint64_t modified;

    /// @brief The size of this file in bytes (0 if this is a directory)
    uint32_t size;

    /// @brief True if this is a directory, false otherwise
    uint32_t isDirectory;
} IODIRENT;

/// @brief Opaque handle to an open directory
typedef void IODIR;

/// @brief Opaque handle to an open file descriptor
typedef void IOFILE;

/// @brief Check if the given storage device is present
/// @param device The storage device (valid values are "cd", "ma", and "mb")
/// @return
extern uint8_t fs_deviceExists(const char *device);

/// @brief Eject the given storage device, if it supports it
/// @param device The storage device (valid values are "cd", "ma", and "mb")
extern void fs_deviceEject(const char *device);

/// @brief Check if the file exists
/// @param filepath Path to the file
/// @return 1 if the file exists, 0 otherwise
extern uint8_t fs_fileExists(const char *filepath);

/// @brief Open a file for reading
/// @param filepath Path to the file to open
/// @param mode Mode to open the file in (valid values are IO_FILEMODE_READ and IO_FILEMODE_WRITE)
/// @return A handle to the open file or NULL if the file could not be opened
extern IOFILE *fs_open(const char *filepath, uint32_t mode);

/// @brief Allocate a new file on the memory card
/// @param filename The name of the file to create (must not exceed 28 characters)
/// @param icon Pointer to a 16x16 4bpp icon to associate with the file
/// @param iconPalette Pointer to an array of RGB565 palette colors to use for the icon
/// @param numBlocks The number of 512-byte blocks to reserve for the file
/// @return A handle to the open file or NULL if the file could not be created
extern IOFILE *fs_allocMemoryCard(const char *filename, const void *icon, const uint16_t *iconPalette, uint32_t numBlocks);

/// @brief Read data from an open file stream
/// @param filehandle A handle previously returned from fs_open
/// @param buffer Buffer to read data into
/// @param readLen Maximum number of bytes to read
/// @return Number of bytes read, or -1 if an error occurred
extern uint32_t fs_read(IOFILE *filehandle, void *buffer, uint32_t readLen);

/// @brief Write to an open file stream
/// @param filehandle A handle previously returned from fs_open
/// @param buffer Buffer to write from
/// @param readLen Number of bytes to write
/// @return Number of bytes written, or -1 if an error occurred
extern uint32_t fs_write(IOFILE *filehandle, const void *buffer, uint32_t readLen);

/// @brief Seek to a position within the open file stream
/// @param filehandle A handle previously returned from fs_open
/// @param position Seek position
/// @param whence Origin to seek relative to
/// @return New absolute position within the stream
extern uint32_t fs_seek(IOFILE *filehandle, int32_t position, uint32_t whence);

/// @brief Flush buffered write data in the filestream to the underlying device
/// @param filehandle A handle previously returned from fs_open
extern void fs_flush(IOFILE *filehandle);

/// @brief Retrieve the current position within the open file stream
/// @param filehandle A handle previously returned from fs_open
/// @return The absolute position within the stream
extern uint32_t fs_tell(IOFILE *filehandle);

/// @brief Retrieve whether the given file stream's position is at its end
/// @param filehandle A handle previously returned from fs_open
/// @return True if the stream has reached its end, false otherwise
extern uint8_t fs_eof(IOFILE *filehandle);

/// @brief Close a previously opened file stream
/// @param filehandle A handle previously returned from fs_open
extern void fs_close(IOFILE *filehandle);

/// @brief Open a directory
/// @param path Path to a directory to open
/// @return A handle to the open directory, or NULL if an error occurred
extern IODIR *fs_openDir(const char *path);

/// @brief Reads the next directory entry from the open directory
/// @param dirHandle A handle previously returned from fs_opendir
/// @return A pointer to a struct with information about the directory entry, or NULL if an error occurred or reached end of directory listing
extern IODIRENT *fs_readDir(IODIR *dirHandle);

/// @brief Rewind open directory to the beginning of the listing
/// @param dirHandle A handle previously returned from fs_opendir
extern void fs_rewindDir(IODIR *dirHandle);

/// @brief Close open directory
/// @param dirHandle A handle previously returned from fs_opendir
extern void fs_closeDir(IODIR *dirHandle);

#ifdef __cplusplus
}
#endif
