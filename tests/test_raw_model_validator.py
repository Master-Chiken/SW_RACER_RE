#!/usr/bin/env python3
"""Regression tests for scripts/validate_raw_model.py."""
from __future__ import annotations
import struct
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import validate_raw_model  # noqa: E402
import extract_raw_model  # noqa: E402


def raw_chunk(mask: bytes, model: bytes, magic: bytes = b"RAWM") -> bytes:
    return magic + struct.pack("<II", len(mask), len(model)) + mask + model


class RawModelValidatorTests(unittest.TestCase):
    def test_rejects_truncated_header(self) -> None:
        problems, _ = validate_raw_model.analyze(b"RAWM")
        self.assertTrue(any("smaller than the 12-byte header" in p for p in problems))

    def test_rejects_bad_magic(self) -> None:
        problems, _ = validate_raw_model.analyze(raw_chunk(bytes(4), b"Comp", b"NOPE"))
        self.assertTrue(any("bad magic" in p for p in problems))

    def test_accepts_minimal_compressed_chunk(self) -> None:
        problems, notes = validate_raw_model.analyze(raw_chunk(bytes(4), b"Comp"))
        self.assertEqual(problems, [])
        self.assertTrue(any("compressed" in n for n in notes))

    def test_rejects_declared_size_mismatch(self) -> None:
        chunk = b"RAWM" + struct.pack("<II", 4, 8) + bytes(8)
        problems, _ = validate_raw_model.analyze(chunk)
        self.assertTrue(any("size mismatch" in p for p in problems))

    def test_rejects_misaligned_mask(self) -> None:
        problems, _ = validate_raw_model.analyze(raw_chunk(b"\x00", b"Modl"))
        self.assertTrue(any("not a multiple of 4" in p for p in problems))
        self.assertTrue(any("expected mask_size" in p for p in problems))

    def test_detects_pointer_past_end_of_model(self) -> None:
        mask = b"\x40\x00\x00\x00"
        model = b"Modl" + struct.pack(">I", 0x100)
        problems, _ = validate_raw_model.analyze(raw_chunk(mask, model))
        self.assertTrue(any("point past the end of the model" in p for p in problems))


    def test_extracts_model_from_valid_block(self) -> None:
        block = struct.pack(">IIII", 1, 16, 20, 24) + bytes(4) + b"Comp"
        mask, model = extract_raw_model.extract_model_bytes(block, 0)
        self.assertEqual(mask, bytes(4))
        self.assertEqual(model, b"Comp")

    def test_rejects_extractor_offset_outside_block(self) -> None:
        block = struct.pack(">IIII", 1, 16, 20, 0x100) + bytes(4) + b"Comp"
        with self.assertRaises(ValueError):
            extract_raw_model.extract_model_bytes(block, 0)

    def test_rejects_truncated_stock_offsets(self) -> None:
        with self.assertRaises(ValueError):
            validate_raw_model.inspect_stock_model(bytes(4), 0)


if __name__ == "__main__":
    unittest.main()
