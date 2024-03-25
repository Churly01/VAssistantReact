const path = require('path');
const webpack = require('webpack');
module.exports = {
  /**
   * This is the main entry point for your application, it's the first file
   * that runs in the main process.
   */
  entry: './src/main.js',
  plugins: [
    new webpack.DefinePlugin({
      'FACE_RECOG_PATH': JSON.stringify(path.resolve(__dirname, 'src/face_recog')),
    })
  ],
  // Put your normal webpack config below here
  module: {
    rules: require('./webpack.rules'),
  },
};
