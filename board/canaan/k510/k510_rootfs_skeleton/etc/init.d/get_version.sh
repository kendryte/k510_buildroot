#!/bin/bash
rel_path=/etc/version/release_version
if [ -f "$rel_path" ]; then
        chmod 444 $rel_path
        cat $rel_path
fi


