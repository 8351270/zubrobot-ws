/// Request.hpp
///
/// 0.0 - created (Denis Rozhkov <denis@rozhkoff.com>)
///

#ifndef __ZUBR_CONNECTOR_WS_REQUEST__H
#define __ZUBR_CONNECTOR_WS_REQUEST__H


#include <memory>
#include <string>

#include "Types.hpp"


namespace zubr {

	class RequestWs : public Serializable {
	protected:
		const static int MethodIdRequest = 9;
		const static int MethodIdSubscribe = 1;
		const static int MethodIdUnsubscribe = 2;

	protected:
		int m_id;
		int m_methodId;
		std::string m_methodName;
		Channel m_channel;

	public:
		RequestWs( const std::string & methodName = "",
			int methodId = MethodIdRequest,
			Channel channel = Channel::_undef )
			: m_methodName( methodName )
			, m_methodId( methodId )
			, m_channel( channel )
			, m_id( 0 )
		{
		}

		static std::shared_ptr<SerializerWs> CreateSerializer();
		static void Serialize( std::string & out, RequestWs & req );

		void Serialize( SerializerWs * o ) override
		{
		}

		void Serialize( SerializerWs * o, RequestWs & req );

		void Id( int id )
		{
			m_id = id;
		}

		int Id() const
		{
			return m_id;
		}

		const std::string & MethodName() const
		{
			return m_methodName;
		}
	};

	/// @brief authentication request
	class AuthRequestWs : public RequestWs {
	protected:
		std::string m_keyId;
		std::string m_keySecret;

	public:
		const static std::string ReqMethodName;

	public:
		/// @brief authentication request
		/// @param keyId
		/// @param keySecret
		/// @return
		AuthRequestWs(
			const std::string & keyId, const std::string & keySecret )
			: RequestWs( ReqMethodName )
			, m_keyId( keyId )
			, m_keySecret( keySecret )
		{
		}

		void Serialize( SerializerWs * o ) override;
	};

	/// @brief place order request
	class PlaceOrderRequestWs : public RequestWs {
	protected:
		int m_instrumentId;
		Number m_price;
		OrderDirection m_direction;
		int m_quantity;
		OrderType m_type;
		OrderLifetime m_lifetime;

	public:
		const static std::string ReqMethodName;

	public:
		/// @brief place order request
		/// @param instrumentId Instrument number
		/// @param price
		/// @param direction Order direction: 'BUY' or 'SELL'
		/// @param quantity Order size quantity
		/// @param type Order type: 'LIMIT' or 'POST_ONLY'
		/// @param lifetime Order lifetime parameter. Has three possible
		/// options:
		///		'GTC' - good 'til cancelled order, active while not cancelled or
		///			executed
		///		'IOC' - immediate or cancel order, unfilled part or
		///			order immediately canceled
		///		'FOK' - fill or kill order, complete
		///			execution or nothing
		/// @return
		PlaceOrderRequestWs( int instrumentId,
			const Number & price,
			OrderDirection direction,
			int quantity,
			OrderType type,
			OrderLifetime lifetime )
			: RequestWs( ReqMethodName )
			, m_instrumentId( instrumentId )
			, m_price( price )
			, m_direction( direction )
			, m_quantity( quantity )
			, m_type( type )
			, m_lifetime( lifetime )
		{
		}

		void Serialize( SerializerWs * o ) override;
	};

	class SubscribeRequestWs : public RequestWs {
	public:
		SubscribeRequestWs( Channel channel )
			: RequestWs( "", MethodIdSubscribe, channel )
		{
		}
	};

} // namespace zubr


#endif
