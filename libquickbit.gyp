{
  'targets': [{
    'target_name': 'libquickbit',
    'type': 'static_library',
    'include_dirs': [
      './include',
    ],
    'dependencies': [
      './vendor/libsimdle/libsimdle.gyp:libsimdle',
    ],
    'sources': [
      './src/quickbit.c',
    ],
    'direct_dependent_settings': {
      'include_dirs': [
        './include',
      ],
    },
    'configurations': {
      'Debug': {
        'defines': ['DEBUG'],
      },
      'Release': {
        'defines': ['NDEBUG'],
      },
    },
  }]
}
