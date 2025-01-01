#include <iostream>
#include <map>
#include <string>
#include "../include/curl/curl.h"
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

int main()
{
    CURL *curl = curl_easy_init();

    if (curl)
    {
        string fromCurrency, toCurrency;
        double amount;

        cout << "=== Currency Converter ===" << endl;

        cout << "Enter source currency (e.g., usd): ";
        cin >> fromCurrency;

        cout << "Enter target currency (e.g., eur): ";
        cin >> toCurrency;

        cout << "Enter amount: ";
        cin >> amount;

       
        const std::string url = "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/" + fromCurrency + ".json";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            try
            {
                // Parse the JSON response
                auto jsonData = json::parse(response);

                // Check if target currency exists in the JSON
                if (jsonData[fromCurrency].contains(toCurrency))
                {
                    double exchangeRate = jsonData[fromCurrency][toCurrency];
                    double convertedAmount = amount * exchangeRate;

                    cout << "Exchange Rate (" << fromCurrency << " to " << toCurrency << "): " << exchangeRate << endl;
                    cout << "Converted Amount: " << convertedAmount << " " << toCurrency << endl;
                }
                else
                {
                    cerr << "Error: Target currency not found in the response!" << endl;
                }
            }
            catch (const json::exception &e)
            {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }
        else
        {
            // If request failed, print error
            cerr << "cURL error: " << curl_easy_strerror(res) << endl;
        }

        // Cleanup CURL object
        curl_easy_cleanup(curl);
    }
    else
    {
        cerr << "Error initializing CURL" << endl;
    }

    return 0;
}
