#!/bin/bash

rsync -avP -e ssh web/ karelklic,wikt@web.sourceforge.net:htdocs/
