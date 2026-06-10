#!/usr/bin/env python3
"""Catedral Framework — QSS generator from tokens.yaml.

Usage:
    python3 build_theme.py
Outputs:
    Catedral.qss in the same directory.
"""
import re
from pathlib import Path
import yaml

HERE = Path(__file__).parent
TOKENS = HERE / "tokens.yaml"
TEMPLATE = HERE / "template.qss.j2"
OUTPUT = HERE / "Catedral.qss"


def flatten(tokens):
    out = {}
    for k, v in tokens.items():
        if isinstance(v, dict):
            for sub, val in v.items():
                out[f"{k}_{sub}"] = val
                out[sub] = val
        else:
            out[k] = v
    return out


def render(template_text, env):
    pattern = re.compile(r"\{([a-zA-Z_][a-zA-Z0-9_]*)\}")

    def sub(m):
        key = m.group(1)
        if key not in env:
            raise KeyError(f"Unknown token: {key}")
        return str(env[key])

    return pattern.sub(sub, template_text)


def main():
    tokens = yaml.safe_load(TOKENS.read_text())
    env = flatten(tokens)
    qss = render(TEMPLATE.read_text(), env)
    OUTPUT.write_text(qss)
    print(f"Wrote {OUTPUT} ({len(qss)} chars)")


if __name__ == "__main__":
    main()
