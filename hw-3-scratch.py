
from typing import Any

import base64, hashlib, json

class SignanytureHandler:
    @property
    def algo_name(self) -> str:
        """ Name of the JWT algorithm. """
        raise NotImplementedError

    def sign(self, jwt_body: bytes) -> bytes:
        """ Generate unencoded signature from unencoded body data. """
        raise NotImplementedError

    def verify(self, jwt_body: bytes, raw_sig: bytes) -> bool:
        """ Verify unencoded body data against unencoded signature. """
        raise NotImplementedError

def b64decode_jwt(data: bytes) -> bytes:
    data += b"="*(len(data)%4)
    return base64.urlsafe_b64decode(data)

#### begin 4 parts total
def encode_jwt(payload: Any, sig_handler: SignatureHandler) -> bytes:
    # the payload is json; a list of key-val pairs
    # ?can we do sanity check to make sure it is valid json
    # ?private-key "your-256-bit-secret" should be param to the hash creating the sig
    h_json = json.dumps({"alg": sig_handler.algo_name, "typ": "JWT"})
    b_json = json.dumps(payload)
    h = base64.urlsafe_b64encode(h_json.encode('utf-8'))
    b = base64.urlsafe_b64encode(b_json.encode('utf-8'))
    signing_input = h + b"." + b
    s = sig_handler.sign(signing_input)

    return h + b"." + b + b"." + s

def decode_jwt(jwt_token: bytes, sig_handlers: dict[str, SignatureHandler]) -> Any:
    segments = jwt_token.split(b".")
    if len(segments) != 3:
        raise ValueError('JWT should have exactly 3 parts')

    h = segments[0]
    b = segments[1]
    s = segments[2]
    try:
        h_json = b64decode_jwt(h).decode('utf-8')
    except Exception as err:
        print('Malformed JWT header')
        raise

    # unmarshal to dictionary
    header_data = json.loads(h_json)
    if not "alg" in header_data:
        raise ValueError('Signature algorithm missing in JWT header')

    algo_name = header_data["alg"]
    verifier = sig_handlers[algo_name]
    if not isinstance(verifier, SignatureHandler):
        raise TypeError('No signature handler with specified algo_name')


    try:
        b_json = b64decode_jwt(b).decode('utf-8')
    except Exception as err:
        print('Malformed JWT body')
        raise

    # is the signature segment valid?
    signing_input = h + b"." + b
    if not verifier.verify(signing_input, s):
        raise ValueError('Signature verification failure')
    return json.loads(b_json)

### to verify the encode/decode
class DummySignature(SignatureHandler):
    HASH_FUNC = {
        256: hashlib.sha256,
        384: hashlib.sha384,
        512: hashlib.sha512
    }

    def __init__(self, hash_bits: int = 256):
        self.hash_bits = hash_bits

        self.hash_func = self.HASH_FUNC[hash_bits]

    @property
    def algo_name(self) -> str:
        return f"DummySig{self.hash_bits}"

    def sign(self, jwt_body: bytes) -> bytes:
        return self.hash_func(jwt_body).digest()

    def verify(self, jwt_body: bytes, raw_sig: bytes) -> bool:
        return self.sign(jwt_body)==raw_sig

# Example JWT payload
example_payload = {"prop1": "value1", "prop2": 42}
# Dummy signature algorithm
dummy_sig = DummySignature()

# Create JWT
jwt_f1 = encode_jwt(example_payload, dummy_sig)
# Decode JWT
decoded_payload_f1 = decode_jwt(jwt_f1, {dummy_sig.algo_name: dummy_sig})

# Decoded JWT payload should match example payload
assert example_payload==decoded_payload_f1


#TODO the exceptions requirements
#### now part II

