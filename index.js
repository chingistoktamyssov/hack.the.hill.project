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
  //only works for devices advertising heart rate service
  // const _options = { filters: [{ services: ["heart_rate"] }] };

  const options = {
    acceptAllDevices: true,
    optionalServices: ["00002a37-0000-1000-8000-00805f9b34fb"],
  };
  device = await navigator.bluetooth.requestDevice(options);
}

async function connectDevice() {
  if (device.gatt.connected) return;

  const server = await device.gatt.connect();
  console.log('abc')
  const service = await server.getPrimaryService("0x180D");
  console.log('io')
  heartRate = await service.getCharacteristic("Heart Rate Measurement");
  console.log('zyx')
  heartRate.addEventListener("characteristicvaluechanged", handleRateChange);
}


async function init() {
  if (!device) await requestDevice();

  connectBTN.textContent = "connecting...";
  await connectDevice();

  beatAudio.play();
  await heartRate.startNotifications();
}

connectBTN.addEventListener("click", init);