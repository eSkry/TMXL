#include "TMXL/TMXLType.h"

namespace TMXL {

    TMXLType::TMXLType() {
        m_type = TMXLTypes::Undefined_e;
        m_data = nullptr;
    }

    TMXLType::TMXLType(const TMXLType& object) : TMXLType() {
        m_type = object.getType();
        switch (m_type){
            case TMXLTypes::Undefined_e: break;
            case TMXLTypes::Int_e: m_data = new int(object.as_int()); break;
            case TMXLTypes::TLSize_e: m_data = new TLSize_t(object.as_int()); break; // TODO as TLSize_t
            case TMXLTypes::Long_e: m_data = new long(object.as_long()); break;
            case TMXLTypes::Bool_e: m_data = new bool(object.as_bool()); break;
            case TMXLTypes::Double_e: m_data = new double(object.as_double()); break;
            case TMXLTypes::String_e: m_data = new sf::String(object.as_string()); break;
            case TMXLTypes::Color_e: m_data = new sf::Color(object.as_color()); break;
        }
    }

    TMXLTypes TMXLType::getType() const noexcept {
        return m_type;
    }

    TMXLType::~TMXLType() {
        deleteData();
    }

    void TMXLType::operator=(int val) noexcept {
        if (m_type == TMXLTypes::Int_e){
            *reinterpret_cast<int*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::Int_e;
        m_data = new int(val);
    }

    void TMXLType::operator=(long val) noexcept {
        if (m_type == TMXLTypes::Long_e){
            *reinterpret_cast<long*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::Long_e;
        m_data = new long(val);
    }

    void TMXLType::operator=(const sf::Color& val) noexcept {
        if (m_type == TMXLTypes::Color_e){
            *reinterpret_cast<sf::Color*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::Color_e;
        m_data = new sf::Color(val);
    }

    void TMXLType::operator=(double val) noexcept {
        if (m_type == TMXLTypes::Double_e) {
            *reinterpret_cast<double*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::Double_e;
        m_data = new double(val);
    }

    void TMXLType::operator=(const sf::String &val) noexcept {
        if (m_type == TMXLTypes::String_e){
            *reinterpret_cast<sf::String*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::String_e;
        m_data = new sf::String(val);
    }

    void TMXLType::operator=(bool val) noexcept {
        if (m_type == TMXLTypes::Bool_e) {
            *reinterpret_cast<bool*>(m_data) = val;
            return;
        }
        deleteData();
        m_type = TMXLTypes::Bool_e;
        m_data = new bool(val);
    }

    void TMXLType::deleteData() noexcept {
        if (m_data) {
            switch (m_type) {
                case TMXLTypes::String_e:		delete reinterpret_cast<sf::String*>(m_data); break;
                case TMXLTypes::Int_e:			delete reinterpret_cast<int*>(m_data); break;
                case TMXLTypes::TLSize_e:		delete reinterpret_cast<TLSize_t*>(m_data); break;
                case TMXLTypes::Double_e:		delete reinterpret_cast<double*>(m_data); break;
                case TMXLTypes::Color_e:		delete reinterpret_cast<sf::Color*>(m_data); break;
                case TMXLTypes::Long_e:			delete reinterpret_cast<long*>(m_data); break;
                case TMXLTypes::Bool_e:			delete reinterpret_cast<bool*>(m_data); break;
                case TMXLTypes::Undefined_e:	break;
            }
        }
    }

    int TMXLType::as_int(int defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return strToInt(*reinterpret_cast<sf::String*>(m_data)); break;
			case TMXL::TMXLTypes::Int_e:		return *reinterpret_cast<int*>(m_data); break;
			case TMXL::TMXLTypes::TLSize_e:		return static_cast<int>(*reinterpret_cast<TLSize_t*>(m_data)); break;
			case TMXL::TMXLTypes::Bool_e:		return intToBool(*reinterpret_cast<bool*>(m_data)); break;
			case TMXL::TMXLTypes::Double_e:		return static_cast<int>(*reinterpret_cast<double*>(m_data)); break;
			case TMXL::TMXLTypes::Color_e:		return colorToInt(*reinterpret_cast<sf::Color*>(m_data)); break;
			case TMXL::TMXLTypes::Long_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

    long TMXLType::as_long(long defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return strToLong(*reinterpret_cast<sf::String*>(m_data)); break;
			case TMXL::TMXLTypes::Int_e:		return *reinterpret_cast<int*>(m_data); break;
			case TMXL::TMXLTypes::Long_e:		return *reinterpret_cast<long*>(m_data); break;
			case TMXL::TMXLTypes::Bool_e:		return boolToLong(*reinterpret_cast<bool*>(m_data)); break;
			case TMXL::TMXLTypes::Double_e:		return static_cast<long>(*reinterpret_cast<double*>(m_data)); break;
			case TMXL::TMXLTypes::Color_e:		return colorToInt(*reinterpret_cast<sf::Color*>(m_data)); break;
			case TMXL::TMXLTypes::TLSize_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

    double TMXLType::as_double(double defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return strToDouble(*reinterpret_cast<sf::String*>(m_data)); break;
			case TMXL::TMXLTypes::Int_e:		return static_cast<double>(*reinterpret_cast<int*>(m_data)); break;
			case TMXL::TMXLTypes::Long_e:		return static_cast<double>(*reinterpret_cast<long*>(m_data)); break;
			case TMXL::TMXLTypes::Bool_e:		return boolToDouble(*reinterpret_cast<bool*>(m_data)); break;
			case TMXL::TMXLTypes::Double_e:		return *reinterpret_cast<double*>(m_data); break;
			case TMXL::TMXLTypes::Color_e:		break;
			case TMXL::TMXLTypes::TLSize_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

    sf::Color TMXLType::as_color(const sf::Color &defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return strToColorARGB(*reinterpret_cast<sf::String*>(m_data)); break;
			case TMXL::TMXLTypes::Int_e:		return intToColor(*reinterpret_cast<int*>(m_data)); break;
			case TMXL::TMXLTypes::Long_e:		return intToColor(*reinterpret_cast<long*>(m_data)); break;
			case TMXL::TMXLTypes::Color_e:		return *reinterpret_cast<sf::Color*>(m_data); break;
			case TMXL::TMXLTypes::TLSize_e:		break;
			case TMXL::TMXLTypes::Bool_e:		break;
			case TMXL::TMXLTypes::Double_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

    sf::String TMXLType::as_string(const sf::String &defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return *reinterpret_cast<sf::String*>(m_data); break;
			case TMXL::TMXLTypes::Int_e:		return intToString(*reinterpret_cast<int*>(m_data)); break;
			case TMXL::TMXLTypes::Long_e:		return longToString(*reinterpret_cast<long*>(m_data)); break;
			case TMXL::TMXLTypes::Bool_e:		return boolToString(*reinterpret_cast<bool*>(m_data)); break;
			case TMXL::TMXLTypes::Color_e:		return colorToStringARGB(*reinterpret_cast<sf::Color*>(m_data)); break;
			case TMXL::TMXLTypes::TLSize_e:		break;
			case TMXL::TMXLTypes::Double_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

    bool TMXLType::as_bool(bool defaultValue) const noexcept {
		switch (m_type) {
			case TMXL::TMXLTypes::String_e:		return strToBool(*reinterpret_cast<sf::String*>(m_data), defaultValue); break;
			case TMXL::TMXLTypes::Int_e:		return intToBool(*reinterpret_cast<int*>(m_data)); break;
			case TMXL::TMXLTypes::Long_e:		return longToBool(*reinterpret_cast<long*>(m_data)); break;
			case TMXL::TMXLTypes::Bool_e:		return *reinterpret_cast<bool*>(m_data); break;
			case TMXL::TMXLTypes::Double_e:		return doubleToBool(*reinterpret_cast<double*>(m_data)); break;
			case TMXL::TMXLTypes::TLSize_e:		break;
			case TMXL::TMXLTypes::Color_e:		break;
			case TMXL::TMXLTypes::Undefined_e:	break;
		}

        return defaultValue;
    }

}