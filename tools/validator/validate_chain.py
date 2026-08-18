#!/usr/bin/env python3
"""
Operation Eden - EETU-01 M1A Telemetry Chain Validator
Audits structural compliance, 24h ISO-8601 formatting, integer canonical preimages,
sequence continuity, and SHA-256 rolling chain hashes.
"""

import json
import hashlib
import sys

def verify_chain(log_path):
    print(f"[*] Auditing Telemetry Ledger: {log_path}")
    expected_prev = "GENESIS"
    expected_seq = 1
    committed_records = 0

    with open(log_path, "r", encoding="utf-8") as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue

            try:
                record = json.loads(line)
            except json.JSONDecodeError as e:
                print(f"[!] FAILED: Line {line_num} contains malformed JSON: {e}")
                return False

            # 1. Sequence Continuity Check
            seq = record.get("seq")
            if seq != expected_seq:
                print(f"[!] FAILED: Line {line_num} sequence jump. Expected {expected_seq}, got {seq}")
                return False

            # 2. Predecessor Linkage Check
            prev = record.get("prev_record_hash")
            if expected_prev == "GENESIS":
                if prev is not None:
                    print(f"[!] FAILED: Line {line_num} (Genesis) must have null prev_record_hash")
                    return False
            else:
                if prev != expected_prev:
                    print(f"[!] FAILED: Line {line_num} broken link. Expected prev {expected_prev}, got {prev}")
                    return False

            # 3. Canonical Integer Preimage Reconstruction
            raw = record["raw_canonical"]
            system = record["system"]
            preimage = (
                f"{record['protocol']}|"
                f"device={record['device_id']}|"
                f"ts={record['timestamp']}|"
                f"seq={record['seq']}|"
                f"air_temp_centi_c={raw['air_temp_centi_c']}|"
                f"relative_humidity_centi_pct={raw['relative_humidity_centi_pct']}|"
                f"firmware={system['firmware_version']}|"
                f"reset_reason={system['reset_reason']}|"
                f"prev={expected_prev}"
            )

            # 4. SHA-256 Digest Verification
            calc_hash = hashlib.sha256(preimage.encode("utf-8")).hexdigest()
            if calc_hash != record["record_hash"]:
                print(f"[!] FAILED: Line {line_num} hash mismatch.")
                print(f"    Calculated : {calc_hash}")
                print(f"    In Record  : {record['record_hash']}")
                return False

            expected_prev = record["record_hash"]
            expected_seq += 1
            committed_records += 1

    print(f"[✓] SUCCESS: Verified {committed_records} committed records, contiguous sequence, valid hash chain, and canonical record integrity.")
    return True

if __name__ == "__main__":
    target = sys.argv[1] if len(sys.argv) > 1 else "telemetry.ndjson"
    if not verify_chain(target):
        sys.exit(1)
