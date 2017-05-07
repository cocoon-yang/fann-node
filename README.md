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
    

## Methods

### Creation, Destruction, Execution

fann-node  | FANN   | Method Description
---------- | -------|-------------------
create_standard_array| fann_create_standard_array | Creates a standard fully connected backpropagation neural network with an array of layer sizes.
create_sparse_array| fann_create_sparse_array |Creates a standard backpropagation neural network, which is not fully connected, with an array of layer sizes.
create_shortcut_array | fann_create_shortcut_array | Creates a standard backpropagation neural network, which is not fully connected and which also has shortcut connections, with an array of layer sizes instead of individual parameters.
destroy | fann_destroy | Destroys the entire network and properly freeing all the associated memmory.
run | fann_run | Will run input through the neural network, returning an array of outputs, the number of which being equal to the number of neurons in the output layer.
print_connections| fann_print_connections | Will print the connections of the ann in a compact matrix, for easy viewing of the internals of the ann.


### FANN Training 

fann-node  | FANN   | Method Description
---------- | -------|-------------------
test | fann_test | Test with a set of inputs, and a set of desired outputs.
get_MSE | fann_get_MSE | Reads the mean square error from the network.
train_on_data | fann_train_on_data | Trains on an entire dataset, for a period of time.
get_training_algorithm | fann_get_training_algorithm |	Return the training algorithm as described by fann_train_enum.
set_training_algorithm | fann_set_training_algorithm |	Set the training algorithm.
get_learning_rate | fann_get_learning_rate |	Return the learning rate.
set_learning_rate | fann_set_learning_rate |	Set the learning rate.
set_activation_function_hidden | fann_set_activation_function_hidden |	Set the activation function for all of the hidden layers.
set_activation_function_output | fann_set_activation_function_output | Set the activation function for the output layer.
set_activation_steepness | fann_set_activation_steepness | Set the activation steepness for neuron number neuron in layer number layer, counting the input layer as layer 0. 
set_activation_steepness_layer | fann_set_activation_steepness_layer |	Set the activation steepness for all of the neurons in layer number layer, counting the input layer as layer 0.
set_activation_steepness_hidden | fann_set_activation_steepness_hidden | Set the steepness of the activation steepness in all of the hidden layers.
set_activation_steepness_output | fann_set_activation_steepness_output | Set the steepness of the activation steepness in the output layer.


### File Input and Output 

fann-node  | FANN   | Method Description
---------- | -------|-------------------
create_from_file | fann_create_from_file | Constructs a backpropagation neural network from a configuration file, which has been saved by fann_save.
save | fann_save | Save the entire network to a configuration file.
