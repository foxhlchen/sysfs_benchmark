#!/bin/bash

modules=(`ls /lib/modules`)
for i in  "${!modules[@]}"; do
    printf "%s\t%s\n" "$i" "${modules[$i]}"
done

read -p "which> " opt_idx
opt=${modules[$opt_idx]}

echo "To delete $opt?"

read -p "y/N >" comfirm

if [[ $comfirm == "y" ]]; then
    echo "Deleting $opt"
    sudo rm -rf /lib/modules/$opt && sudo rm -f /boot/*${opt}* && echo "Done" || echo "Failed!"
fi


    
