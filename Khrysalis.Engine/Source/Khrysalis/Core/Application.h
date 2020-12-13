#pragma once

int main(int argc, char** argv);

namespace Khrysalis {
	struct Version {
		Version(uint8_t major, uint8_t minor, uint8_t patch) : Major(major), Minor(minor), Patch(patch) {}

		uint8_t Major, Minor, Patch;
	};

	class Application {
	public:
		explicit Application(const std::string& name, const Version& version = { 1, 0, 0 });
		virtual ~Application() = default;

		static Application& Get() { return *Instance; }

		const std::string& GetName() { return _name; }
		const Version& GetVersion() { return _version; }

		void SetName(const std::string& name) { _name = name; }
		void SetVersion(const Version& version) { _version = version; }

	private:
		void Run();

	private:
		static Application* Instance;

		std::string _name;
		Version _version;

		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}