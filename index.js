const appUI = document.querySelector(".ui");
const bpmTxt = document.querySelector(".bpm");
const stopBTN = document.querySelector(".stop");
const heartUI = document.querySelector(".heart");
const startBTN = document.querySelector(".start");
const errorTxt = document.querySelector(".error");
const beatAudio = document.querySelector("audio");
const connectBTN = document.querySelector(".connect");
const connectUI = document.querySelector(".connect-ui");

let device;
let heartRate;

function parseHeartRate(value) {
  let is16Bits = value.getUint8(0) & 0x1;
  if (is16Bits) return value.getUint16(1, true);
  return value.getUint8(1);
}

function handleRateChange(event) {
  bpmTxt.textContent = parseHeartRate(event.target.value);
}

async function requestDevice() {
  const options = {
    acceptAllDevices: true,
    optionalServices: ["heart_rate"],
  };
  device = await navigator.bluetooth.requestDevice(options);
}

async function connectDevice() {
  if (device.gatt.connected) return;

  const server = await device.gatt.connect();
  const service = await server.getPrimaryService("heart_rate");
  heartRate = await service.getCharacteristic("heart_rate_measurement");
  heartRate.addEventListener("characteristicvaluechanged", handleRateChange);
  console.log(heartRate)
}

async function init() {
  if (!device) await requestDevice();

  connectBTN.textContent = "connected";
  while(1) {
    await connectDevice();
    beatAudio.play();
}
}

connectBTN.addEventListener("click", init);