const { spawn } = require('child_process');
const path = require("path");

const cpprocess = spawn(path.join(__dirname, './main'));

cpprocess.stdout.on('data', (data) => {
  console.log(`stdout: ${data}`);
});
