#include "food_order.h"

int process_food_order(struct OrderRequest *request)
{
	if (!request)
		return -1; // Invalid request

	switch (check_restaurant_status(request))
	{
	case 1: // Restaurant is open
		// Create a standard confirmation
		struct OrderConfirmation *confirmation = create_standard_confirmation();
		if (!confirmation)
			return -2; // Failed to create confirmation

		// Send the confirmation notification
		send_confirmation_notification(confirmation);
		free(confirmation); // Free the confirmation after sending
		return 0;			// Success

	case 0: // Restaurant is closed
		// Create a pre-order confirmation
		struct OrderConfirmation *preorder_confirmation = create_preorder_confirmation();
		if (!preorder_confirmation)
			return -3; // Failed to create pre-order confirmation

		// Send the pre-order confirmation notification
		send_confirmation_notification(preorder_confirmation);
		free(preorder_confirmation); // Free the pre-order confirmation after sending
		return 0;					 // Success

	default:
		return -4; // Unknown status
	}
}