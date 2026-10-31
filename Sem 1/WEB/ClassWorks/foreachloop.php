<?php

$arr = array("Peter=>35", "Ben=>37", "Joe=>43");
echo sort($arr);
foreach($arr as $key => $value) {
    echo "$key $value<br>";
}

?>