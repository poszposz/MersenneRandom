
generateENTOutputFile() {
	sequenceLength=$1
	alphabet=$2
	method=$3
	sequenceOutputFile=$4
	numberOfGeneratedSequences=$5
	resultFile=$6
	#///////////////////
	entropySum=0
	chiSum=0
	meanSum=0
	correlationSum=0
	#///////////////////
	entropyMean=0
	chiMean=0
	meanMean=0
	correlationMean=0
	#///////////////////
	entropyMin=100000000
	chiMin=100000000
	meanMin=100000000
	correlationMin=100000000
	#///////////////////
	entropyMax=-100000000
	chiMax=-100000000
	meanMax=-100000000
	correlationMax=-100000000
	#///////////////////
	for ((i=0; i<$numberOfGeneratedSequences; i++)); do
		touch $sequenceOutputFile$i.txt
		./mers_rand $sequenceLength $alphabet $method $sequenceOutputFile$i.txt
		OUTPUT="$(ent -c $sequenceOutputFile$i.txt)"
		entropy=$(sed 's/^.*Entropy = //; s/ bits per byte..*$//' <<< $OUTPUT)
		chi=$(sed 's/^.*samples is //; s/ and randomly would exceed this.*$//' <<< $OUTPUT)
		chi=$(sed 's/,//' <<< $chi)
		mean=$(sed 's/^.*mean value of data bytes is //; s/ (127.5 = random).*$//' <<< $OUTPUT)
		correlation=$(sed 's/^.*Serial correlation coefficient is //; s/ (totally uncorrelated = 0.0)..*$//' <<< $OUTPUT)
		entropySum=$(echo "$entropySum + $entropy"|bc)
		chiSum=$(echo "$chiSum + $chi"|bc)
		meanSum=$(echo "$meanSum + $mean"|bc)
		correlationSum=$(echo "$correlationSum + $correlation"|bc)
		# ////////////////////////////////////////////////////////////////////////////////////////////
		if (( $(echo "$entropy > $entropyMax" |bc -l) )); then
			echo "Found entropy max"
			entropyMax=$entropy
		fi
		if (( $(echo "$entropy < $entropyMin" |bc -l) )); then
			echo "Found entropy min"
			entropyMin=$entropy
		fi
		# ////////////////////////////////////////////////////////////////////////////////////////////
		if (( $(echo "$chi > $chiMax" |bc -l) )); then
			echo "Found chi max"
			chiMax=$chi
		fi
		if (( $(echo "$chi < $chiMin" |bc -l) )); then
			echo "Found chi min"
			chiMin=$chi
		fi
		# ////////////////////////////////////////////////////////////////////////////////////////////
		if (( $(echo "$correlation > $correlationMax" |bc -l) )); then
			echo "Found correlation max"
			correlationMax=$correlation
		fi
		if (( $(echo "$correlation < $correlationMin" |bc -l) )); then
			echo "Found correlation min"
			correlationMin=$correlation
		fi
		# ////////////////////////////////////////////////////////////////////////////////////////////
		if (( $(echo "$mean > $meanMax" |bc -l) )); then
			echo "Found mean max"
			meanMax=$mean
		fi
		if (( $(echo "$mean < $meanMin" |bc -l) )); then
			echo "Found mean min"
			meanMin=$mean
		fi
		# ////////////////////////////////////////////////////////////////////////////////////////////
	done
	entropyMean=$(echo "$entropySum/$numberOfGeneratedSequences"|bc -l)
	chiMean=$(echo "$chiSum/$numberOfGeneratedSequences"|bc -l)
	correlationMean=$(echo "$correlationSum/$numberOfGeneratedSequences"|bc -l)
	meanMean=$(echo "$meanSum/$numberOfGeneratedSequences"|bc -l)

	echo "Entropy mean: "$entropyMean > $resultFile
	echo "Chi mean: "$chiMean >> $resultFile
	echo "Correlation mean: "$correlationMean >> $resultFile
	echo "Mean mean: "$meanMean >> $resultFile

	echo "Entropy minimum: "$entropyMin >> $resultFile
	echo "Entropy maximum: "$entropyMax >> $resultFile

	echo "Chi minimum: "$chiMin >> $resultFile
	echo "Chi maximum: "$chiMax >> $resultFile

	echo "Correlation minimum: "$correlationMin >> $resultFile
	echo "Correlation maximum: "$correlationMax >> $resultFile

	echo "Mean minimum: "$meanMin >> $resultFile
	echo "Mean maximum: "$meanMax >> $resultFile
}

echo "Analyzing with different alphabets"
mkdir generator_results
chmod 777 ./generator_results/tmp.txt
mkdir ./generator_results/ent_results

mkdir ./generator_results/ent_results/diff_alphabet
mkdir ./generator_results/mersenne_diff_alphabet
mkdir ./generator_results/minSTD_diff_alphabet
mkdir ./generator_results/knuth_diff_alphabet

timesVal=10

MER_62_FILE_NAME="mersenne_62_diff_alphabet"
generateENTOutputFile 100000 62 "mer" "./generator_results/mersenne_diff_alphabet/$MER_62_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/mersenne_alphabet_62_times_100.txt

MIN_62_FILE_NAME="minSTD_62_diff_alphabet"
generateENTOutputFile 100000 62 "min" "./generator_results/minSTD_diff_alphabet/$MIN_62_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/minSTD_alphabet_62_times_100.txt

KNU_62_FILE_NAME="knuth_62_diff_alphabet"
generateENTOutputFile 100000 62 "knu" "./generator_results/knuth_diff_alphabet/$KNU_62_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/knuth_alphabet_62_times_100.txt

MER_20_FILE_NAME="mersenne_20_diff_alphabet"
generateENTOutputFile 100000 20 "mer" "./generator_results/mersenne_diff_alphabet/$MER_20_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/mersenne_alphabet_20_times_100.txt

MIN_20_FILE_NAME="minSTD_20_diff_alphabet"
generateENTOutputFile 100000 20 "min" "./generator_results/minSTD_diff_alphabet/$MIN_20_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/minSTD_alphabet_20_times_100.txt

KNU_20_FILE_NAME="knuth_20_diff_alphabet"
generateENTOutputFile 100000 20 "knu" "./generator_results/knuth_diff_alphabet/$KNU_20_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/knuth_alphabet_20_times_100.txt

MER_15_FILE_NAME="mersenne_15_diff_alphabet"
generateENTOutputFile 100000 15 "mer" "./generator_results/mersenne_diff_alphabet/$MER_15_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/mersenne_alphabet_15_times_100.txt

MIN_15_FILE_NAME="minSTD_15_diff_alphabet"
generateENTOutputFile 100000 15 "min" "./generator_results/minSTD_diff_alphabet/$MIN_15_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/minSTD_alphabet_15_times_100.txt

KNU_15_FILE_NAME="knuth_15_diff_alphabet"
generateENTOutputFile 100000 15 "knu" "./generator_results/knuth_diff_alphabet/$KNU_15_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/knuth_alphabet_15_times_100.txt

MER_10_FILE_NAME="mersenne_10_diff_alphabet"
generateENTOutputFile 100000 10 "mer" "./generator_results/mersenne_diff_alphabet/$MER_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/mersenne_alphabet_10_times_100.txt

MIN_10_FILE_NAME="minSTD_10_diff_alphabet"
generateENTOutputFile 100000 10 "min" "./generator_results/minSTD_diff_alphabet/$MIN_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/minSTD_alphabet_10_times_100.txt

KNU_10_FILE_NAME="knuth_10_diff_alphabet"
generateENTOutputFile 100000 10 "knu" "./generator_results/knuth_diff_alphabet/$KNU_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/knuth_alphabet_10_times_100.txt

MER_5_FILE_NAME="mersenne_5_diff_alphabet"
generateENTOutputFile 100000 5 "mer" "./generator_results/mersenne_diff_alphabet/$MER_5_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/mersenne_alphabet_5_times_100.txt

MIN_5_FILE_NAME="minSTD_5_diff_alphabet"
generateENTOutputFile 100000 5 "min" "./generator_results/minSTD_diff_alphabet/$MIN_5_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/minSTD_alphabet_5_times_100.txt

KNU_5_FILE_NAME="knuth_5_diff_alphabet"
generateENTOutputFile 100000 5 "knu" "./generator_results/knuth_diff_alphabet/$KNU_5_FILE_NAME" $timesVal ./generator_results/ent_results/diff_alphabet/knuth_alphabet_5_times_100.txt

echo "Analyzing with different sequence lengths."
mkdir ./generator_results/ent_results/diff_sequence_length
mkdir ./generator_results/mersenne_diff_sequence_length
mkdir ./generator_results/minSTD_diff_sequence_length
mkdir ./generator_results/knuth_diff_sequence_length

times1Value=10000000
times2Value=100000
times3Value=10000
times4Value=1000
times5Value=100
times6Value=10

MER_TIMES_10000000_FILE_NAME="mersenne_10000000_diff_sequence_length"
generateENTOutputFile $times1Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_10000000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_10000000_times_100.txt

MIN_TIMES_10000000_FILE_NAME="minSTD_10000000_diff_sequence_length"
generateENTOutputFile $times1Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_10000000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_10000000_times_100.txt

KNU_TIMES_10000000_FILE_NAME="knuth_10000000_diff_sequence_length"
generateENTOutputFile $times1Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_10000000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_10000000_times_100.txt


MER_TIMES_100000_FILE_NAME="mersenne_100000_diff_sequence_length"
generateENTOutputFile $times2Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_100000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_100000_times_100.txt

MIN_TIMES_100000_FILE_NAME="minSTD_100000_diff_sequence_length"
generateENTOutputFile $times2Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_100000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_100000_times_100.txt

KNU_TIMES_100000_FILE_NAME="knuth_100000_diff_sequence_length"
generateENTOutputFile $times2Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_100000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_100000_times_100.txt


MER_TIMES_10000_FILE_NAME="mersenne_10000_diff_sequence_length"
generateENTOutputFile $times3Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_10000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_10000_times_100.txt

MIN_TIMES_10000_FILE_NAME="minSTD_10000_diff_sequence_length"
generateENTOutputFile $times3Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_10000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_10000_times_100.txt

KNU_TIMES_10000_FILE_NAME="knuth_10000_diff_sequence_length"
generateENTOutputFile $times3Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_10000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_10000_times_100.txt


MER_TIMES_1000_FILE_NAME="mersenne_10000_diff_sequence_length"
generateENTOutputFile $times4Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_1000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_1000_times_100.txt

MIN_TIMES_1000_FILE_NAME="minSTD_10000_diff_sequence_length"
generateENTOutputFile $times4Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_1000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_1000_times_100.txt

KNU_TIMES_1000_FILE_NAME="knuth_10000_diff_sequence_length"
generateENTOutputFile $times4Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_1000_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_1000_times_100.txt


MER_TIMES_100_FILE_NAME="mersenne_10000_diff_sequence_length"
generateENTOutputFile $times5Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_100_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_100_times_100.txt

MIN_TIMES_100_FILE_NAME="minSTD_10000_diff_sequence_length"
generateENTOutputFile $times5Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_100_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_100_times_100.txt

KNU_TIMES_100_FILE_NAME="knuth_10000_diff_sequence_length"
generateENTOutputFile $times5Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_100_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_100_times_100.txt


MER_TIMES_10_FILE_NAME="mersenne_10000_diff_sequence_length"
generateENTOutputFile $times6Value 62 "mer" "./generator_results/mersenne_diff_sequence_length/$MER_TIMES_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/mersenne_sequence_10_times_100.txt

MIN_TIMES_10_FILE_NAME="minSTD_10000_diff_sequence_length"
generateENTOutputFile $times6Value 62 "mer" "./generator_results/minSTD_diff_sequence_length/$MIN_TIMES_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/minSTD_sequence_10_times_100.txt

KNU_TIMES_10_FILE_NAME="knuth_10000_diff_sequence_length"
generateENTOutputFile $times6Value 62 "mer" "./generator_results/knuth_diff_sequence_length/$KNU_TIMES_10_FILE_NAME" $timesVal ./generator_results/ent_results/diff_sequence_length/knuth_sequence_10_times_100.txt







