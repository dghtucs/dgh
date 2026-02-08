#include <cstdio>
#include <cctype>

const int MAX_LEN = 1000005;  // Maximum input length
const int MAX_DEG = 65;       // Maximum degree of polynomials
const int M = 1000000007;     // Modulus

char input[MAX_LEN];
int pos = 0;                  // Current position in input

// Polynomial structure
struct Polynomial {
    long long coef[MAX_DEG];  // Coefficients from degree 0 to MAX_DEG - 1

    // Initialize polynomial to zero
    void init() {
        for (int i = 0; i < MAX_DEG; i++) {
            coef[i] = 0;
        }
    }

    // Copy another polynomial
    void copy(const Polynomial& other) {
        for (int i = 0; i < MAX_DEG; i++) {
            coef[i] = other.coef[i];
        }
    }

    // Add another polynomial
    void add(const Polynomial& other) {
        for (int i = 0; i < MAX_DEG; i++) {
            coef[i] = (coef[i] + other.coef[i]) % M;
        }
    }

    // Subtract another polynomial
    void subtract(const Polynomial& other) {
        for (int i = 0; i < MAX_DEG; i++) {
            coef[i] = (coef[i] - other.coef[i]) % M;
            if (coef[i] < 0) coef[i] += M;
        }
    }

    // Multiply by another polynomial
    void multiply(const Polynomial& other) {
        long long result[MAX_DEG] = {0};
        for (int i = 0; i < MAX_DEG; i++) {
            if (coef[i] == 0) continue;
            for (int j = 0; j < MAX_DEG; j++) {
                if (other.coef[j] == 0) continue;
                if (i + j < MAX_DEG) {
                    result[i + j] = (result[i + j] + coef[i] * other.coef[j]) % M;
                }
            }
        }
        for (int i = 0; i < MAX_DEG; i++) {
            coef[i] = result[i];
        }
    }

    // Raise polynomial to the k-th power (k <= 4)
    void power(int k) {
        Polynomial result;
        result.init();
        result.coef[0] = 1;  // Initialize result to 1

        Polynomial base;
        base.copy(*this);

        while (k > 0) {
            if (k % 2 == 1) {
                result.multiply(base);
            }
            base.multiply(base);
            k /= 2;
        }
        copy(result);
    }

    // Output the polynomial
    void output() {
        // Find highest degree with non-zero coefficient
        int highest_deg = -1;
        for (int i = MAX_DEG - 1; i >= 0; i--) {
            if (coef[i] != 0) {
                highest_deg = i;
                break;
            }
        }
        if (highest_deg == -1) {
            // Polynomial is zero
            printf("0\n");
            return;
        }
        // Output coefficients from highest to lowest degree
        for (int i = highest_deg; i >= 0; i--) {
            printf("%lld", coef[i]);
            if (i > 0) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }
};

// Forward declarations
void parseExpression(Polynomial& result);
void parseTerm(Polynomial& result);
void parseFactor(Polynomial& result);
void parseBase(Polynomial& result);

// Helper functions
void skipWhitespace() {
    while (input[pos] == ' ') pos++;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Parse a number
long long parseNumber() {
    long long num = 0;
    while (isDigit(input[pos])) {
        num = num * 10 + (input[pos] - '0');
        pos++;
    }
    return num;
}

// Main parsing functions

// Parse an expression: term { ('+' | '-') term }
void parseExpression(Polynomial& result) {
    parseTerm(result);
    while (true) {
        if (input[pos] == '+') {
            pos++;
            Polynomial term;
            term.init();
            parseTerm(term);
            result.add(term);
        } else if (input[pos] == '-') {
            pos++;
            Polynomial term;
            term.init();
            parseTerm(term);
            result.subtract(term);
        } else {
            break;
        }
    }
}

// Parse a term: factor { '*' factor }
void parseTerm(Polynomial& result) {
    parseFactor(result);
    while (true) {
        // Handle omitted multiplication signs
        bool omittedMultiplication = false;
        int prevPos = pos;
        if (input[pos] == '\0' || input[pos] == ')' || input[pos] == '+' || input[pos] == '-') {
            break;
        }
        if (input[pos] == '*') {
            pos++;
        } else {
            // Check for omitted multiplication
            char curr = input[pos];
            char prev = input[prevPos - 1];
            if ((isDigit(prev) || prev == 'x' || prev == ')') && (input[pos] == '(' || input[pos] == 'x')) {
                omittedMultiplication = true;
            } else {
                break;
            }
        }
        Polynomial factor;
        factor.init();
        parseFactor(factor);
        result.multiply(factor);
    }
}

// Parse a factor: base { '^' number }
void parseFactor(Polynomial& result) {
    parseBase(result);
    while (input[pos] == '^') {
        pos++;
        // Exponent must be a positive integer
        int exponent = (int)parseNumber();
        if (exponent < 0 || exponent > 4) exponent = 1;
        result.power(exponent);
    }
}

// Parse a base: number | x | '(' expression ')' | '-' base
void parseBase(Polynomial& result) {
    skipWhitespace();
    if (input[pos] == '(') {
        pos++;  // Consume '('
        parseExpression(result);
        if (input[pos] == ')') {
            pos++;  // Consume ')'
        }
    } else if (input[pos] == 'x') {
        pos++;  // Consume 'x'
        result.init();
        result.coef[1] = 1;
    } else if (input[pos] == '-') {
        pos++;  // Consume '-'
        Polynomial base;
        base.init();
        parseBase(base);
        for (int i = 0; i < MAX_DEG; i++) {
            result.coef[i] = (-base.coef[i]) % M;
            if (result.coef[i] < 0) result.coef[i] += M;
        }
    } else if (isDigit(input[pos])) {
        long long num = parseNumber();
        result.init();
        result.coef[0] = num % M;
    } else {
        // Invalid character, treat as zero
        result.init();
        pos++;
    }
}

int main() {
    // Read input
    int len = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        input[len++] = c;
    }
    input[len] = '\0';

    pos = 0;
    Polynomial result;
    result.init();
    parseExpression(result);
    result.output();

    return 0;
}
