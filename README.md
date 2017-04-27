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

## Examples:  
<pre> 
// 
// Global variables
var fann = new yfann.YNodeFANN( );
var test_data = new yfann.YNodeFANNTrainData( );
var train_data = new yfann.YNodeFANNTrainData( );
 
// 
// Methods
 function pumadyn()
 {
  	var num_layers = 3;
 	var num_neurons_hidden = 32;
 	var desired_error =  0.0001;
 	var max_epochs = 300;
 	var epochs_between_reports = 10;
 	
 	console.log("Creating network.\n");
 	
 	test_data.read_train_from_file('../datasets/pumadyn-32fm.test');
    train_data.read_train_from_file('../datasets/pumadyn-32fm.train');
    
    
 	var input = train_data.num_input_train_data()
	var output = train_data.num_output_train_data()

	console.log( ' input: ', input );
	console.log( 'output: ', output );
 
 	fann.create_standard_array(num_layers, [input, num_neurons_hidden,  output]);
	fann.set_activation_function_hidden(  6 ); // FANN_SIGMOID_SYMMETRIC_STEPWISE)
	fann.set_activation_function_output( 4 );	// FANN_SIGMOID_STEPWISE	
	
 	fann.train_on_data( train_data, max_epochs, epochs_between_reports, desired_error);	
	
	console.log("Testing network.\n");	 
 	var testdata = [0.485265,0.496498,0.503016,0.490695,0.485165,0.489131,0.505908,0.506213,0.502395,0.505477,0.499453,0.504030,0.830962,0.629794,0.883773,0.588814,0.400239,0.523277,0.515112,0.520103,0.518687,0.524354,0.512448,0.517644,0.515489,0.515527,0.512288,0.511747,0.514934,0.517329,0.513065,0.517594]
 	
 	// var result = fann.test( testdata, Array([0.416431]) );
 	var result = fann.run( testdata  ); 	
	console.log( 'result:', result  );
	
	fann.test_data( test_data); 
 }
 
 pumadyn();
 </pre>

<pre>   
//
// module
var yfann = require('./build/release/fann')


//
// network parameters
//
var fann = new yfann.YNodeFANN( );
var test_data = new yfann.YNodeFANNTrainData( );
var train_data = new yfann.YNodeFANNTrainData( );

fann.create_standard_array( 3, [2, 5, 1]  );


var data = [
    [[0, 0], [0]],
    [[0, 1], [1]],
    [[1, 0], [1]],
    [[1, 1], [0]],
    [[0, 0], [0]],
    [[0, 1], [1]],
    [[0, 0], [0]],
];

 
train_data.set_train_data( data );
fann.train_on_data( train_data, 10, 3, 0.01  );
 
console.log("xor test (0,0) -> ", fann.run([0, 0]));
console.log("xor test (1,0) -> ", fann.run([1, 0]));
console.log("xor test (0,1) -> ", fann.run([0, 1]));
console.log("xor test (1,1) -> ", fann.run([1, 1]));
</pre>    
 
 Tips:
      When you running test.js, don't forget copy the fann libraries into the directory where test.js lies in.
    
