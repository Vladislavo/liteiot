#include <gateway_protocol.h>


void gateway_protocol_packet_encode (
    const uint8_t dev_id, 
    const gateway_protocol_packet_type_t packet_type,
    const uint8_t payload_length,
    const uint8_t *payload,
    uint8_t *packet_length,
    uint8_t *packet)
{
    *packet_length = 0;

    packet[*packet_length] = dev_id;
    packet_length++;

    packet[*packet_length] = packet_type;
    (*packet_length)++;

    memcpy(&packet[*packet_length], payload, payload_length);
    *packet_length += payload_length;
}

uint8_t gateway_protocol_packet_decode (
    uint8_t *dev_id, 
    gateway_protocol_packet_type_t *packet_type,
    uint8_t *payload_length,
    uint8_t *payload,
    const uint8_t packet_length,
    const uint8_t *packet)
{
    uint8_t p_len = 0;

    *dev_id = packet[p_len];
    p_len++;

    *packet_type = (gateway_protocol_packet_type_t) packet[p_len];
    p_len++;

    *payload_length = packet_length - p_len;

    memcpy(payload, &packet[p_len], *payload_length);
    p_len += *payload_length;

    return (p_len == packet_length);
}