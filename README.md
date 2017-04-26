# fann-node
Node.js interface of Fast Artificial Neural Network Library (FANN) 2.2.0 on Windows 

## Directories:    
   inc -- head files of FANN and fann-node addon \
   src -- source files of FANN and fann-node addon \
   tmp -- Makefile \
  node -- head files of Node.js (version 4.3.0) \
   lib -- libraries of FANN and Node.js

Compile
--
 open developer command prompt for VS   
    
<pre>
tmp> nmake  
</pre>

## Example:  
<pre> 
// 
// Global variables
var fann = new yfann.YNodeFANN( );
var test_data = new yfann.YNodeFANNTrainData( );
var train_data = new yfann.YNodeFANNTrainData( );
 
// 
// Methods
function cascade()
{
	test_data.read_train_from_file('./parity8.train');
	train_data.read_train_from_file('./parity8.test');

	var input = train_data.num_input_train_data()
	var output = train_data.num_output_train_data()

	console.log( ' input: ', input );
	console.log( 'output: ', output );

	train_data.scale_train_data( -1, 1);
	test_data.scale_train_data( -1, 1);
	
	fann.create_shortcut(2, input, output );
	
	fann.set_training_algorithm( 2 );  // FANN_TRAIN_RPROP;
	fann.set_activation_function_hidden( 5 );  // ann, FANN_SIGMOID_SYMMETRIC
	fann.set_activation_function_output( 0 );  // ann, FANN_LINEAR
	fann.set_train_error_function( 0 );	 // ann, FANN_ERRORFUNC_LINEAR
		
	var testdata = []
	var result = fann.run( testdata );
	console.log( 'result:', result[0]  );	
 }   
 cascade();
 </pre>
