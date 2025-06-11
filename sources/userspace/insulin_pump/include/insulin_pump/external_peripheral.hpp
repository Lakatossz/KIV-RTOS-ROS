#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <unordered_set>

#ifdef _WIN32
	#ifdef ZM_EXTERNAL_PERIPHERAL_EXPORT
		#define ZM_EXTERNAL_PERIPHERAL_API __declspec(dllexport)
	#else
		#define ZM_EXTERNAL_PERIPHERAL_API __declspec(dllimport)
	#endif
#else
	#define ZM_EXTERNAL_PERIPHERAL_AP
#endif

class IExternal_Peripheral
{
public:
	/// Alias for a function that sets the value of a GPIO pin
	using Set_GPIO_Pin_t = int (*)(std::uint32_t, bool);

	/// Alias for a function that reads the value of a GPIO pin
	using Read_GPIO_Pin_t = bool (*)(std::uint32_t);

	// -------------------------------------------------------------------------------------------------------------
	/// \enum NInit_Status
	/// \brief Defines values that can be returned from the #Create_Peripheral function.
	// -------------------------------------------------------------------------------------------------------------
	enum class NInit_Status : std::uint32_t
	{
		OK = 0,          ///< All went well
		GPIO_Mismatch,   ///< Number of GPIO pins does not match the expected value
		Allocation_Error ///< Failed to create (allocate) the peripheral
	};

public:
	// -------------------------------------------------------------------------------------------------------------
	/// \brief Creates an instance of the class
	// -------------------------------------------------------------------------------------------------------------
	IExternal_Peripheral() = default;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Destroys (deletes) the object from the memory.
	// -------------------------------------------------------------------------------------------------------------
	virtual ~IExternal_Peripheral() = default;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Deleted copy constructor (rule of five).
	// -------------------------------------------------------------------------------------------------------------
	IExternal_Peripheral(const IExternal_Peripheral&) = delete;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Deleted assignment operator (rule of five).
	/// \return Instance of this class
	// -------------------------------------------------------------------------------------------------------------
	IExternal_Peripheral& operator=(const IExternal_Peripheral&) = delete;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Deleted move constructor (rule of five).
	// -------------------------------------------------------------------------------------------------------------
	IExternal_Peripheral(IExternal_Peripheral&&) = delete;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Deleted assignment operator with an r-value reference (rule of five).
	/// \return Instance of this class
	// -------------------------------------------------------------------------------------------------------------
	IExternal_Peripheral& operator=(IExternal_Peripheral&&) = delete;

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Returns a collection of GPIO pins the peripheral subscribes to.
	///
	/// The peripheral gets notified whenever the state of any of the listed pins changes.
	///
	/// \return Collection of GPIO pins the peripheral subscribes to
	// -------------------------------------------------------------------------------------------------------------
	[[nodiscard]] const std::unordered_set<std::uint32_t>& Get_GPIO_Subscription() const
	{
		return m_gpio_subscription;
	}

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Notifies the peripheral that the state of one of the pins it subscribes to has changed.
	/// \note The peripheral may choose not to subscribe to any GPIO pins (e.g. when it is an input peripheral)
	/// \param pin_idx Index of the GPIO pin whose state has been changed
	// -------------------------------------------------------------------------------------------------------------
	[[maybe_unused]] virtual void GPIO_Subscription_Callback([[maybe_unused]] std::uint32_t pin_idx)
	{
	}

	// -------------------------------------------------------------------------------------------------------------
	/// \brief Notifies the peripheral about how many CPU cycles have passed by.
	///
	/// The CPU core calls this function after every instruction, so the peripheral can update itself.
	///
	/// \note In reality, external peripherals do not know of CPU cycles - simplification (e.g. UART)
	/// \param count Number of CPU cycles
	// -------------------------------------------------------------------------------------------------------------
	[[maybe_unused]] virtual void Increment_Passed_Cycles([[maybe_unused]] std::uint32_t count)
	{
	}

protected:
	std::unordered_set<std::uint32_t> m_gpio_subscription{}; ///< Collection of GPIO the peripheral subscribes to
};

extern "C"
{
	// -----------------------------------------------------------------------------------------------------------------
	/// \brief Creates an instance of an external peripheral.
	///
	/// This function is called outside the shared library. It is called by the emulator when it attempts to attach
	/// the peripheral to the GPIO pins.
	///
	/// \param peripheral Pointer to a pointer to an external peripheral (the actual pointer is in the emulator)
	/// \param name Unique name of the peripheral (e.g. "My button")
	/// \param gpio_pins Collection of GPIO pins the peripherals is hooked up to
	/// \param pin_count Number of GPIO pins used by the peripheral
	/// \param set_pin Reference to a function the peripheral can use to set GPIO pins
	/// \param read_pin Reference to a function the peripheral can use to read values of GPIO pins
	/// \param logging_system Pointer to the logging system that is used throughout the project
	/// \return 0, if all goes well and the peripheral is created successfully. 1, otherwise.
	// -----------------------------------------------------------------------------------------------------------------
	ZM_EXTERNAL_PERIPHERAL_API IExternal_Peripheral::NInit_Status
		Create_Peripheral(IExternal_Peripheral** peripheral,
			const char* const name,
			const std::uint32_t* const connection,
			std::size_t pin_count,
			[[maybe_unused]] IExternal_Peripheral::Set_GPIO_Pin_t set_pin,
			[[maybe_unused]] IExternal_Peripheral::Read_GPIO_Pin_t read_pin);
			//[[maybe_unused]] zero_mate::utils::CLogging_System* logging_system);
}