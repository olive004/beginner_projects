#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul 31 16:53:56 2019

@author: oliviagallup
"""


# Following https://pythonprogramming.net/tensorflow-deep-neural-network-machine-learning-tutorial/

# Importing the hot stuff
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("/tmp/data/", one_hot = True)


# Building da nets xxx (nodes n shit)
n_nodes_hl1 = 500
n_nodes_hl2 = 500
n_nodes_hl3 = 500
n_classes = 10
batch_size = 100


# Da variables of interest (SO RANDOM LOL XD)
x = tf.placeholder('float', [None, 784])
y = tf.placeholder('float')


# The NNM (neUrAl NEtWorK mODEL)
def neural_network_model(data):
    # Random weights whoah
    hidden_1_layer = {'weights':tf.Variable(tf.random_normal([784, n_nodes_hl1])),
                      'biases':tf.Variable(tf.random_normal([n_nodes_hl1]))}

    hidden_2_layer = {'weights':tf.Variable(tf.random_normal([n_nodes_hl1, n_nodes_hl2])),
                      'biases':tf.Variable(tf.random_normal([n_nodes_hl2]))}

    hidden_3_layer = {'weights':tf.Variable(tf.random_normal([n_nodes_hl2, n_nodes_hl3])),
                      'biases':tf.Variable(tf.random_normal([n_nodes_hl3]))}

    output_layer = {'weights':tf.Variable(tf.random_normal([n_nodes_hl3, n_classes])),
                    'biases':tf.Variable(tf.random_normal([n_classes]))}
    
    
    # Getting bussyyy adding those biases and feeding forward gggg
    l1 = tf.add(tf.matmul(data,hidden_1_layer['weights']), hidden_1_layer['biases'])
    l1 = tf.nn.relu(l1)

    l2 = tf.add(tf.matmul(l1,hidden_2_layer['weights']), hidden_2_layer['biases'])
    l2 = tf.nn.relu(l2)

    l3 = tf.add(tf.matmul(l2,hidden_3_layer['weights']), hidden_3_layer['biases'])
    l3 = tf.nn.relu(l3)

    output = tf.matmul(l3,output_layer['weights']) + output_layer['biases']

    return output


# Under a new function, train_neural_network, we will pass data. We then produce a prediction based on the output of that data through our neural_network_model. Next, we create a cost variable. This measures how wrong we are, and is the variable we desire to minimize by manipulating our weights.
def train_neural_network(x):
    prediction = neural_network_model(x)
    cost = tf.reduce_mean( tf.nn.softmax_cross_entropy_with_logits(logits=prediction, labels=y) )
    
    # Optimizing the cost, using an optimizer like Stochastic Gradient Descent and AdaGrad; 
    # AdamOptimizer has learning rate of 0.001 automatically
    optimizer = tf.train.AdamOptimizer().minimize(cost)
    
    
    # Using 10 epochs (cycles of feed forward and back prop)
    hm_epochs = 10
    with tf.Session() as sess:
        # initialize variables
        sess.run(tf.global_variables_initializer())
        
        # juicy bit
        
        for epoch in range(hm_epochs):
            epoch_loss = 0
            for _ in range(int(mnist.train.num_examples/batch_size)):
                epoch_x, epoch_y = mnist.train.next_batch(batch_size)
                _, c = sess.run([optimizer, cost], feed_dict={x: epoch_x, y: epoch_y})
                epoch_loss += c

            # For each epoch, we output the total loss, which should be declining each time
            print('Epoch', epoch, 'completed out of',hm_epochs,'loss:',epoch_loss)
            
        # How many predictions did we make that actually were right? 
        correct = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
        
        # Final accuracy on the testing data
        accuracy = tf.reduce_mean(tf.cast(correct, 'float'))
        print('Accuracy:',accuracy.eval({x:mnist.test.images, y:mnist.test.labels}))
    
    
# dun dun dun
train_neural_network(x)
    
    