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



## [FANN Parameters](http://leenissen.dk/fann/wp/help/advanced-usage/)


### Training Algorithm

"The training algorithm is one of the most important parameters. 
The training algorithms have several different parameters which can be set. the most important parameter is the learning rate, but unfortunately this is also a parameter which is hard to find a reasonable default for.
 I (SN) have several times ended up using 0.7, but it is a good idea to test several different learning rates when training a network.  It is also worth noting that the activation function has a profound effect on the optimal learning rate"[1]

### Weights

The initial weights are random values between -0.1 and 0.1. Thimm and Fiesler state that, “An (sic) fixed weight variance of 0.2, which corresponds to a weight range of [-0.77, 0.77], gave the best mean performance for all the applications tested in this study.  This performance is similar or better as compared to those of the other weight initialization methods.”

### Activation Function  

The standard activation function is the sigmoid activation function, the steepness parameter used in the activation function can be adjusted[1].

### Layers, Neurons and Connections

"If the network become too large, the ANN will have difficulties learning and when it does learn it will tend to over-fit resulting in poor generalization.  If the network becomes too small, it will not be able to represent the rules needed to learn the problem and it will never gain a sufficiently low error rate."[1]

"The number of hidden layers is also important.  Generally speaking, if the problem is simple it is often enough to have one or two hidden layers, but as the problems get more complex, so does the need for more layers."[1]

### Adjusting Parameters During Training

"The threshold activation function is faster than the sigmoid function, but since it is not possible to train with this function, you may wish to consider an alternate approach."[1]

"While training the ANN you could slightly increase the steepness parameter of the sigmoid function.  This would make the sigmoid function more steep and make it look more like the threshold function.  After this training session you could set the activation function to the threshold function and the ANN would work with this activation function.  This approach will not work on all kinds of problems, but has been successfully tested on the XOR function."[1]


## Valuable References 

[1](http://leenissen.dk/fann/wp/help/advanced-usage/) http://leenissen.dk/fann/wp/help/advanced-usage/

[A Basic Introduction to Feedforward Backpropagation Neural Networks](http://www.webpages.ttu.edu/dleverin/neural_network/neural_networks.html)

[Role of Bias in Neural Networks](http://stackoverflow.com/questions/2480650/role-of-bias-in-neural-networks)

[How to choose number of hidden layers](http://stackoverflow.com/questions/9436209/how-to-choose-number-of-hidden-layers-and-nodes-in-neural-network)  

[Criteria for choosing number of hidden layers ](http://stackoverflow.com/questions/10565868/multi-layer-perceptron-mlp-architecture-criteria-for-choosing-number-of-hidde)

[ann step by step](https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/)
