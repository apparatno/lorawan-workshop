function decodeUplink(input) {
  return {
    data: {
      temperature: parseFloat(String.fromCharCode(...input.bytes))
    },
    warnings: [],
    errors: []
  };
}
