'use strict';

module.exports = function(grunt) {
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-simple-mocha');

  grunt.initConfig({
    jshint: {
      files: [
        '**/*.js',
        '!node_modules/**/*',
        '!build/**/*'
      ],
      options: {
        jshintrc: true
      }
    },

    copy: {
      readme: {
        cwd: 'test/',
        expand: true,
        src: ['README.md'],
        dest: './'
      }
    },

    simplemocha: {
      src: ['test/**/*.js']
    }
  });

  grunt.registerTask('default', [
    'jshint',
    'copy',
    'simplemocha'
  ]);
};
