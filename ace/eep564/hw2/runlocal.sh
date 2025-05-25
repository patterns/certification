#!/bin/sh


# also possible to activate manually
#source .venv/bin/activate
#python local.py

# and to purge
#uv cache clean

# manually remove old datasets
####rm -rf ~/.keras/datasets/*

# command to run script
uv run --offline --with tensorflow localhw2.py

##uv run --with tensorflow local.py

