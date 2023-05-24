#!/bin/bash
script_dir=$(dirname $0)
PROGRAM_PATH="${script_dir}/../zemladan"
OUTPUT_FILE="x.txt"
CONFIG_FILE="cfg_test.config"

incorrect_inputs=(
    "--brightness -ya1"
    "--brightness y101"
    "-brightness 50"
    "--brightenss 50"
    "--invertt"
    "-invert"
    "--scale -1y"
    "--scale 1d01"
    "-scale 50"
    "--sccale 50"
    "--rotate 361d"
    "--rotate -d1"
    "-rotate 180"
    "--rotatee 180"
    "--flipd-horizontal"
    "--flip-verticall"
    "-flip-horizontal"
    "--flipp-horizontal"
    "--fancyy"
    "-fancy"
)

input_files=(
    "${script_dir}/../examples/nonexistent.jpg"
    "${script_dir}/../examples/cat1.jpg"
    "${script_dir}/../examples/cat1.jpg --file $OUTPUT_FILE ${script_dir}/../examples/cat_corrupt.jpg"
    "${script_dir}/../examples/cat1.jpg --file $OUTPUT_FILE"
)

echo "scale=1.5
invertt=flase
brightness=-1
flip=horizontall
flip=vertical
rotate=370
fancy=trye" > $CONFIG_FILE

echo "Testing: $PROGRAM_PATH --conf $CONFIG_FILE ${input_files[2]}"
$PROGRAM_PATH --conf $CONFIG_FILE ${input_files[2]}
if [ $? -eq 0 ]; then
    echo "Test failed."
else
    echo "Test passed."
fi

for input in "${input_files[@]}"; do
    for incorrect_input in "${incorrect_inputs[@]}"; do
        echo "Testing: $PROGRAM_PATH $input $incorrect_input"
        $PROGRAM_PATH $input $incorrect_input
        if [ $? -eq 0 ]; then
            echo "Test failed."
        else
            echo "Test passed."
        fi
    done
done

rm $OUTPUT_FILE
rm $CONFIG_FILE
