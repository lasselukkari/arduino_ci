require "spec_helper"

RSpec.describe ArduinoCI::ArduinoCmd do
  context "autolocate" do
    it "Finds the Arduino executable" do
      arduino_cmd = ArduinoCI::ArduinoCmd.autolocate
    end
  end

  context "autolocate!" do
    it "Finds the Arduino executable" do
      arduino_cmd = ArduinoCI::ArduinoCmd.autolocate!
      expect(arduino_cmd.installation.cmd_path).not_to be nil
      expect(arduino_cmd.prefs_cache.class).to be Hash
      expect(arduino_cmd.prefs_response_time).not_to be nil
    end
  end

  context "board_installed?" do
    arduino_cmd = ArduinoCI::ArduinoCmd.autolocate!
    ArduinoCI::DisplayManager::instance.enable
    it "Finds installed boards" do
      uno_installed = arduino_cmd.board_installed? "arduino:avr:uno"
      expect(uno_installed).to be true
      expect(uno_installed).not_to be nil
    end

    it "Doesn't find bogus boards" do
      bogus_installed = arduino_cmd.board_installed? "eggs:milk:wheat"
      expect(bogus_installed).to be false
      expect(bogus_installed).not_to be nil
    end
  end

  context "set_pref" do
    arduino_cmd = ArduinoCI::ArduinoCmd.autolocate!
    ArduinoCI::DisplayManager::instance.enable

    it "Sets key to what it was before" do
      upload_verify = arduino_cmd.prefs_cache["upload.verify"]
      result = arduino_cmd.set_pref("upload.verify", upload_verify)
      expect(result).to be true
    end
  end
end