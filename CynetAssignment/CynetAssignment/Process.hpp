#pragma once

#include <cstdint>
#include <string>
#include <filesystem>

class Process
{
public:
    explicit Process(uint16_t pid);
    virtual ~Process() = default;

    std::string Serialize() const;

private:
    // TODO (ASK):
    // read cmdline from /proc/[pid]/cmdline (optional: handle zombieness)
    // full path / inode by dereferecing /proc/[pid]/exe
    // fds from /proc/[pid]/fd/
    // /proc/[pid]/stat or status for ppid (pppid can be obtained from parent file), vsize\VmSize (virtual mem size), uid
    static std::filesystem::path get_process_stat_file_path(uint16_t process_id);
    static std::filesystem::path get_process_cmdline_file_path(uint16_t process_id);

    static uint16_t get_parent_id(uint16_t process_id);
    static uint16_t get_grandparent_id(uint16_t parent_id);

private:
    uint16_t _id;
    uint16_t _parent_id;
    uint16_t _grandparent_id;
    std::string _command_line;
    std::string _file_name;  // TODO (ASK) consider grouping file properties under file class
    std::filesystem::path _file_path;
    uint64_t _file_size;
    uint32_t _file_inode;
    uint64_t _virtual_memory_size;
    uint32_t _uid;
    uint16_t _open_fds_count;
};

