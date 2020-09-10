<?php
# collin gros
# 09-09-2020
# this program proves php short circuits if statements by showing the
# function retTrue() is not called when a conditional of 0 && retTrue().

# returns true, and prints that we are inside
function retTrue()
{
    echo "in retTrue\n";
    return true;
}


# won't print anything
if (0 && retTrue()) {
    echo "true";
}

echo "hello";
