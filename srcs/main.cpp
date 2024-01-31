#include "../includes/vulkanHelper.hpp"
#include "../includes/Colors.hpp"
int main()
{
	VulkanHelper	app;

	try {
		app.run();
	} catch (const std::exception& error) {
		std::cerr << C_WHITE << "Exception thrown: ❌" << C_END << std::endl;
		std::cerr << error.what() << std::endl;
		return 1;
	}
	return 0;
}