#!/bin/bash
kill -s 9 $(ps -e | grep python | awk '{print $1}')
