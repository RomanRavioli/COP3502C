#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a constant for maximum name length
#define MAX_NAME 101

// Structure to represent a magical material for a role
struct mag_mat_for_role {
		int type;                // Index of the material in the materials array
		long long amount_needed; // Amount of this material needed for the role
};

// Structure to represent a role
struct role {
		int materials_needed;             // Number of materials needed for this role
		struct mag_mat_for_role *item_list; // List of materials needed for this role
};

// Structure to represent a magical material in the main list
struct mag_mat_for_list {
		char mat_name[MAX_NAME];       // Name of the material
		long long total_amount_needed; // Total amount needed across all roles
		long long magic_required;      // Magic required to create this material
};

// Function to calculate the total magic required
long long calculate_total_magic(int N, struct role *roles, int M, struct mag_mat_for_list *materials, int *denizens_per_role) {
		long long total_magic = 0;
		// Iterate through all roles
		for (int i = 0; i < N; i++) {
				// For each material needed by this role
				for (int j = 0; j < roles[i].materials_needed; j++) {
						int mat_index = roles[i].item_list[j].type;
						// Calculate magic required and add to total
						total_magic += roles[i].item_list[j].amount_needed * materials[mat_index].magic_required * denizens_per_role[i];
				}
		}
		return total_magic;
}

// Function to find the index of a material in the materials array
int find_material_index(char *name, struct mag_mat_for_list *materials, int M) {
		for (int i = 0; i < M; i++) {
				if (strcmp(name, materials[i].mat_name) == 0) {
						return i;
				}
		}
		return -1; // Return -1 if material not found
}

int main() {
		int N, M = 0, D, U;

		// Read number of roles
		scanf("%d", &N);

		// Allocate memory for roles and materials
		struct role *roles = malloc(N * sizeof(struct role));
		struct mag_mat_for_list *materials = malloc(100000 * sizeof(struct mag_mat_for_list));

		// Read information for each role
		for (int i = 0; i < N; i++) {
				scanf("%d", &roles[i].materials_needed);
				roles[i].item_list = malloc(roles[i].materials_needed * sizeof(struct mag_mat_for_role));

				// Read materials for this role
				for (int j = 0; j < roles[i].materials_needed; j++) {
						char mat_name[MAX_NAME];
						scanf("%s %lld", mat_name, &roles[i].item_list[j].amount_needed);

						// Find or add material to the materials list
						int mat_index = find_material_index(mat_name, materials, M);
						if (mat_index == -1) {
								// New material, add to list
								strcpy(materials[M].mat_name, mat_name);
								materials[M].total_amount_needed = roles[i].item_list[j].amount_needed;
								roles[i].item_list[j].type = M;
								M++;
						} else {
								// Existing material, update total amount
								materials[mat_index].total_amount_needed += roles[i].item_list[j].amount_needed;
								roles[i].item_list[j].type = mat_index;
						}
				}
		}

		// Read magic required for each material
		for (int i = 0; i < M; i++) {
				scanf("%s %lld", materials[i].mat_name, &materials[i].magic_required);
		}

		// Read number of denizens
		scanf("%d", &D);
		int *denizens_per_role = calloc(N, sizeof(int));
		// Read role for each denizen
		for (int i = 0; i < D; i++) {
				int role;
				scanf("%d", &role);
				denizens_per_role[role - 1]++;
		}

		// Read number of updates
		scanf("%d", &U);
		// Process each update
		for (int i = 0; i < U; i++) {
				int update_type;
				scanf("%d", &update_type);

				if (update_type == 1) {
						// Update magic required for a material
						char mat_name[MAX_NAME];
						long long new_magic;
						scanf("%s %lld", mat_name, &new_magic);
						int mat_index = find_material_index(mat_name, materials, M);
						materials[mat_index].magic_required = new_magic;
				} else if (update_type == 2) {
						// Update amount of material needed for a role
						int role, new_amount;
						char mat_name[MAX_NAME];
						scanf("%d %s %d", &role, mat_name, &new_amount);
						role--; // Adjust for 0-based indexing
						int mat_index = find_material_index(mat_name, materials, M);
						for (int j = 0; j < roles[role].materials_needed; j++) {
								if (roles[role].item_list[j].type == mat_index) {
										// Update total amount needed
										materials[mat_index].total_amount_needed -= roles[role].item_list[j].amount_needed * denizens_per_role[role];
										materials[mat_index].total_amount_needed += new_amount * denizens_per_role[role];
										roles[role].item_list[j].amount_needed = new_amount;
										break;
								}
						}
				}

				// Calculate and print total magic required after update
				printf("%lld\n", calculate_total_magic(N, roles, M, materials, denizens_per_role));
		}

		// Free allocated memory
		for (int i = 0; i < N; i++) {
				free(roles[i].item_list);
		}
		free(roles);
		free(materials);
		free(denizens_per_role);

		return 0;
}