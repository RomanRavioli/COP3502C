#include <stdio.h>
#include <string.h>

// Function prototype
int isPartOf(char *spell1, char *spell2);

int main() {
		char spells[100][101]; // 100 spells with 100 characters each
		int totalSpells = 0; // Spell cpunter
		int uniqueSpellsCount = 0; // Unique spell counter
		char input[101];

		// Loops until user types "END"
		while (fgets(input, sizeof(input), stdin)) {
				if (strcmp(input, "END\n") == 0 || strcmp(input, "END") == 0) {
						break;
				}
				// Remove "\n"
				size_t len = strlen(input);
				if (len > 0 && input[len - 1] == '\n') {
						input[len - 1] = '\0';
				}
				strcpy(spells[totalSpells++], input);
		}

		// Checks if incantation is inside another
		for (int i = 0; i < totalSpells; i++) {
				int isDerivative = 0;
				for (int j = 0; j < totalSpells; j++) {
						if (i != j && isPartOf(spells[j], spells[i])) {
								isDerivative = 1;
								break;
						}
				}
				if (!isDerivative) {
						uniqueSpellsCount++;
				}
		}

		// Print result
		printf("%d\n", uniqueSpellsCount);

		return 0;
}

// Checks if an incantation is inside another
int isPartOf(char *spell1, char *spell2) {
		int len1 = strlen(spell1);
		int len2 = strlen(spell2);
		for (int i = 0; i <= len1 - len2; i++) {
				int j;
				for (j = 0; j < len2; j++) {
						if (spell1[i + j] != spell2[j]) {
								break;
						}
				}
				if (j == len2) {
						return 1;
				}
		}
		return 0;
}