#include "../dinput_hook/virtual_block_policy.h"

#include <cstdint>
#include <iostream>
#include <limits>

namespace {
int failures = 0;

void check(bool condition, const char *name) {
    if (condition) {
        std::cout << "PASS: " << name << '\n';
    } else {
        std::cerr << "FAIL: " << name << '\n';
        ++failures;
    }
}
}

int main() {
    using namespace virtual_block_policy;
    uint64_t words = 0;
    uint64_t header = 0;

    check(words_per_entry(Kind::Model, &words) && words == 2,
          "model format uses two words per entry");
    check(words_per_entry(Kind::Spline, &words) && words == 1,
          "spline format uses one word per entry");
    check(words_per_entry(Kind::Texture, &words) && words == 2,
          "texture format uses two words per entry");
    check(!words_per_entry(Kind::Model, nullptr), "words-per-entry rejects null output");

    check(table_header_size(Kind::Model, 1, &header) && header == 16,
          "one-entry model header includes terminal offset");
    check(table_header_size(Kind::Spline, 1, &header) && header == 12,
          "one-entry spline header includes terminal offset");
    check(table_header_size(Kind::Texture, 1, &header) && header == 12,
          "one-entry texture header matches two-word entry");
    check(table_header_size(Kind::Texture, 0, &header) && header == 4,
          "empty texture header is just the count");
    check(!table_header_size(Kind::Model, kMaxBlockEntries + 1, &header),
          "table sizing rejects unreasonable entry count");
    check(!table_header_size(Kind::Model, 1, nullptr), "table sizing rejects null output");

    check(source_table_fits(Kind::Model, 1, 16), "exact-size model table fits");
    check(!source_table_fits(Kind::Model, 1, 15), "truncated model table is rejected");
    check(!source_table_fits(Kind::Spline, 1, 11), "truncated spline table is rejected");
    check(!source_table_fits(Kind::Texture, 1, 11), "truncated texture table is rejected");
    check(!source_table_fits(Kind::Spline, kMaxBlockEntries + 1, 64ULL * 1024ULL * 1024ULL),
          "source table rejects unreasonable entry count");
    check(!source_table_fits(Kind::Model, 0, 3), "source shorter than count field is rejected");

    check(source_entry_range_valid(16, 100, 16, 40), "payload range starting at table end is accepted");
    check(source_entry_range_valid(16, 100, 100, 100), "empty terminal range at EOF is accepted");
    check(!source_entry_range_valid(16, 100, 15, 40), "payload before table end is rejected");
    check(!source_entry_range_valid(16, 100, 40, 39), "reversed payload range is rejected");
    check(!source_entry_range_valid(16, 100, 40, 101), "payload past EOF is rejected");

    check(source_model_split_valid(16, 20, 32), "model mask split inside payload is accepted");
    check(!source_model_split_valid(16, 16, 32), "non-empty model rejects split at start");
    check(!source_model_split_valid(16, 33, 32), "model rejects split past entry end");
    check(source_model_split_valid(16, 16, 16), "empty source model entry remains accepted");

    check(source_texture_split_valid(16, 0, 40), "texture without palette is accepted");
    check(source_texture_split_valid(16, 16, 40), "palette beginning at pixel payload is accepted");
    check(source_texture_split_valid(16, 40, 40), "palette ending at entry end is accepted");
    check(!source_texture_split_valid(16, 15, 40), "texture palette before pixels is rejected");
    check(!source_texture_split_valid(16, 41, 40), "texture palette past entry end is rejected");

    return failures == 0 ? 0 : 1;
}
