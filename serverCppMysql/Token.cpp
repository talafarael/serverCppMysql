#include "Token.h"
#include <string>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>
std::string Token::generateToken(std::string id)
{
    try {

        std::string secret_key = "my_secret_key";

        
        std::string token = jwt::create()
            .set_payload_claim("id", jwt::claim(id)) 
            .sign(jwt::algorithm::hs256{ secret_key });     
       
        return token;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка создания токена: " << e.what() << std::endl;
    }
    }



std::string Token::decodeToken(std::string& token) {
    try {
        std::string secret_key = "my_secret_key";

        
        auto decoded = jwt::decode(token);

        
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{ secret_key })
            .with_claim("id", decoded.get_payload_claim("id")); 

        verifier.verify(decoded);

        
        for (const auto& e : decoded.get_payload_json()) {
            std::cout << e.first << " = " << e.second << std::endl;
        }

        
        return decoded.get_payload();
    }
    catch (const jwt::error::token_verification_exception& e) {
        std::cerr << "Ошибка верификации токена: " << e.what() << std::endl;
        return "";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return "";
    }
}