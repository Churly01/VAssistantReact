const rules = require('./webpack.rules');
const webpack = require('webpack');
const path = require('path');

rules.push({
  test: /\.css$/,
  use: ['style-loader', 'css-loader', 'postcss-loader'],
});

module.exports = {
  // Put your normal webpack config below here
  resolve: {
    extensions: ['.js', '.jsx', '.json'],
  },
  plugins: [
    new webpack.HotModuleReplacementPlugin(),
    new webpack.ProvidePlugin({
      'React': 'react'
    })
  ],
  entry: './src/index.js',
  module: {
    rules,
  },
};
